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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "quaternions", NULL, NULL);
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
    Cone cone(100, 1, .2, .4);
    Sphere sphere(100, .5, 1, .2, .4);
    Torus torus(100, .75, .25, 1, .2, .4);

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

    SU2Quat rot(PI/4, Vector4(0.0, 0.0, 1.0, 0.0));

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // which shape to use
    unsigned int s = 0;
    // variable to tell previous state of SPACEKEY
    unsigned int space_state = GLFW_RELEASE;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window, space_state, s);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use the shader
        shader.use();

        // set shader variables
        unsigned int zvecLoc = glGetUniformLocation(shader.id(), "zvec");
        glUniform2fv(zvecLoc, 1, GL_FALSE, { rot.mtx(0,0).real(), rot.mtx(0,0).imag() });
        unsigned int wvecLoc = glGetUniformLocation(shader.id(), "wvec");
        glUniform2fv(wvecLoc, 1, GL_FALSE, { rot.mtx(0,1).real(), rot.mtx(0,1).imag() });

        // render the shape
        glBindVertexArray(VAO[s]);
        glDrawArrays(GL_TRIANGLES, 0, shapes[s].coords.size()*sizeof(float));

        // update state of slash and space key
        space_state = glfwGetKey(window, GLFW_KEY_SPACE);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
