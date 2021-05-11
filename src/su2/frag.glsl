#version 330 core

in vec3 myFragPos;
in vec3 myColor;

out vec4 fragColor;

void main() {
    vec3 result  = myColor;
    fragColor = vec4(result, 1.0f);
}
