cmake_minimum_required(VERSION 3.0)
project(quats VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEPS_DIR "../deps")

set(GLFW_DIR ${DEPS_DIR}/glfw)
add_subdirectory(${GLFW_DIR} ${CMAKE_CURRENT_BINARY_DIR}/glfw)
include_directories(${GLFW_DIR}/include)

set(GLAD_DIR ${DEPS_DIR}/glad)
set(GLAD_C ${GLAD_DIR}/src/glad.c)
include_directories(${GLAD_DIR}/include)

set(CSCI441_DIR ${DEPS_DIR}/csci441)
include_directories(${CSCI441_DIR}/include)

set(GLM_DIR ${DEPS_DIR}/glm)
include_directories(${GLM_DIR})

set(PROJ ${PROJECT_NAME})
add_executable(${PROJ} main.cpp ${GLAD_C})
target_link_libraries(${PROJ} glfw ${GLFW_LIBRARIES})
