#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNorm;

uniform mat4 model;           // transform the model
uniform mat4 camera;          // transform into camera space
uniform mat4 projection;      // project the scene

uniform mat3 model_invt;      // inverse transpose of model matrix
uniform mat3 camera_invt;     // inverse transpose of camera matrix

out vec3 ourColor;
out vec3 ourPos;
out vec3 ourNorm;

void main() {
    // compute gl_Position
    gl_Position = projection * camera * model * vec4(aPos, 1.0f);

    // set output variables
    ourColor = aColor;
    ourPos = (camera * model * vec4(aPos, 1.0f)).xyz;
    ourNorm = normalize(camera_invt * model_invt * aNorm);
}
