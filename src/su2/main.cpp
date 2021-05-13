#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix4.h>
#include <csci441/vector4.h>
#include <csci441/uniform.h>

#include "shape.h"
#include "su2quat.cpp"
#include "compmtx2.cpp"

#define PI 3.1415926535

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

void processInput(GLFWwindow *window, unsigned int &space_state, unsigned int &shape) {
    if (isPressed(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    // decide which shape to use
    if (isPressed(window, GLFW_KEY_SPACE) && space_state == GLFW_RELEASE) {
      shape = (shape + 1) % 5;
    }
}

int main(void) {
    /* Initialize the library */
    GLFWwindow* window;
    if (!glfwInit()) { return -1; }

    int width  = 640;
    int height = 480;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "quaternions", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // create c
    DiscoCube cube;
    Cylinder cylinder(200, 1, .2, .4);
    Cone cone(200, .2, 1, .4);
    Sphere sphere(200, .5, .4, .2, 1);
    Torus torus(200, .5, .25, .4, 1, .2);

    // array for shapes
    Shape shapes[5] = { cube, cylinder, cone, sphere, torus };
    // arrays for vertex buffer and vertex array objects
    GLuint VBO[5];  GLuint VAO[5];

    for (unsigned int s = 0; s < 5; s++) {
      // copy vertex data
      glGenBuffers(1, &VBO[s]);
      glBindBuffer(GL_ARRAY_BUFFER, VBO[s]);
      glBufferData(GL_ARRAY_BUFFER, shapes[s].coords.size()*sizeof(float),
              &shapes[s].coords[0], GL_STATIC_DRAW);

      // describe vertex layout
      glGenVertexArrays(1, &VAO[s]);
      glBindVertexArray(VAO[s]);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float)));
      glEnableVertexAttribArray(2);
    }

    // enable z-buffering
    glEnable(GL_DEPTH_TEST);

    // set up light shading
    Vector4 ambient_intensity(0.15, 0.15, 0.15);
    Vector4 light_pos(2, 1.5, 2);
    Vector4 intensity(1, 1, 1);
    Vector4 eye(0, 0, 1);
    float power = 64.0f;

    Vector4 axis(1.0, 1.0, 1.0, 0.0);
    SU2Quat rot(0, axis);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");
    shader.use();

    float plane = 1.5;
    Matrix4 projection;
    projection.ortho(-plane, plane, -plane, plane, -plane, plane);

    // set up output file
    // start ffmpeg telling it to expect raw rgba 720p-60hz frames
    // -i - tells it to read frames from stdin
    const char* cmd = "ffmpeg -r 120 -f rawvideo -pix_fmt rgba -s 640x480 -i - "
                      "-threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip output.mp4";

    // open pipe to ffmpeg's stdin in binary write mode
    FILE* ffmpeg = _popen(cmd, "wb");
    int* buffer = new int[width*height];

    // which shape to use
    unsigned int s = 0;
    float period = 3.0;
    // variable to tell previous state of SPACEKEY
    unsigned int space_state = GLFW_RELEASE;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window, space_state, s);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // use the shader
        shader.use();

        Uniform::set(shader.id(), "projection", projection);
        Uniform::set(shader.id(), "ambient", ambient_intensity);
        Uniform::set(shader.id(), "light_pos", light_pos);
        Uniform::set(shader.id(), "intensity", intensity);
        Uniform::set(shader.id(), "eye", eye);
        Uniform::set(shader.id(), "power", power);

        rot = SU2Quat(2*PI*std::sin(glfwGetTime()/period), axis);

        // set shader variables
        GLuint zvecLoc = glGetUniformLocation(shader.id(), "zvec");
        GLuint wvecLoc = glGetUniformLocation(shader.id(), "wvec");
        glUniform2f(zvecLoc, rot.mtx(0,0).real(), rot.mtx(0,0).imag());
        glUniform2f(wvecLoc, rot.mtx(0,1).real(), rot.mtx(0,1).imag());

        // render the shape
        glBindVertexArray(VAO[s]);
        glDrawArrays(GL_TRIANGLES, 0, shapes[s].coords.size()*sizeof(float));

        // update state of slash and space key
        space_state = glfwGetKey(window, GLFW_KEY_SPACE);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        fwrite(buffer, sizeof(int)*width*height, 1, ffmpeg);
        glfwPollEvents();
    }

    _pclose(ffmpeg);

    glfwTerminate();
    return 0;
}
