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

#include "shapes.h"
#include "quat.cpp"

#define PI 3.1415926535
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

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
    if (isPressed(window, GLFW_KEY_ESCAPE)) {// || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    // decide which shape to use
    if (isPressed(window, GLFW_KEY_SPACE) && space_state == GLFW_RELEASE) {
      shape = (shape + 1) % 5;
    }
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "quaternions", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
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
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
              (void*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
              (void*)(3*sizeof(float)));
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
              (void*)(6*sizeof(float)));
      glEnableVertexAttribArray(2);
    }

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // setup view
    Vector4 eye(0, 0, -1);
    Vector4 origin(0, 0, 0);
    Vector4 up(0, 1, 0, 0);

    // light settings
    Vector4 ambient_intensity(0.15, 0.15, 0.15);
    Vector4 light_pos(2, 1.5, -2);
    Vector4 intensity(1, 1, 1);
    float power = 64.0f;

    // which shape to use
    unsigned int s = 0;
    // variable to tell previous state of SPACEKEY
    unsigned int space_state = GLFW_RELEASE;

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // declare matrices
    Matrix4 model;        Matrix4 camera;             Matrix4 projection;
    // matrix inverses
    Matrix3 model_invt;   Matrix3 camera_invt;

    // set matrix values
    float plane = 2.5;
    projection.ortho(-plane, plane, -plane, plane, -plane, plane);
    camera.look_at(eye, origin, up);

    // set up quaterions
    Quat src(0.0f, Vector4(0.0f, 0.0f, 1.0f, 0.0f));
    Quat dst(PI, Vector4(1.0f, 1.0f, 1.0f, 0.0f));
    Quat interp;

    // set up timing
    float period = 3.0f;
    float time = 0.0f;
    int int_time = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window, space_state, s);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        int_time = (int)(glfwGetTime()/period);
        time = glfwGetTime()/period;
        interp = src.slerp(dst, time-int_time);
        model = interp.to_matrix();

        // compute transformation for normals
        model_invt.inverse_transpose(model);
        camera_invt.inverse_transpose(camera);

        // set matrix transformations
        Uniform::set(shader.id(), "model", model);
        Uniform::set(shader.id(), "model_invt", model_invt);
        Uniform::set(shader.id(), "camera", camera);
        Uniform::set(shader.id(), "camera_invt", camera_invt);
        Uniform::set(shader.id(), "projection", projection);

        // light settings
        Uniform::set(shader.id(), "ambient", ambient_intensity);
        Uniform::set(shader.id(), "light_pos", light_pos);
        Uniform::set(shader.id(), "intensity", intensity);
        Uniform::set(shader.id(), "power", power);

        // render the cube
        glBindVertexArray(VAO[s]);
        glDrawArrays(GL_TRIANGLES, 0, shapes[s].coords.size()*sizeof(float));

        // update state of slash and space key
        space_state = glfwGetKey(window, GLFW_KEY_SPACE);

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
