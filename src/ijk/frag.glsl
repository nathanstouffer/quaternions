#version 330 core
in vec3 ourColor;
in vec3 ourPos;
in vec3 ourNorm;

uniform mat4 model;              // model matrix
uniform mat4 camera;             // camera matrix

uniform vec3 light_pos;          // position of the light
uniform vec3 intensity;          // light intensity
uniform vec3 ambient;            // ambient light intensity

uniform float power;             // power for phong shading calculation

out vec4 fragColor;

void main() {
    // transform light position into camera space
    vec3 ourLight = (camera * vec4(light_pos, 1.0f)).xyz;

    // compute diffuse shading
    vec3 l = normalize(ourLight - ourPos);                          // vector in direction on the light
    float n_dot_l = dot(ourNorm, l);                                // compute dot product
    if (n_dot_l < 0.0f) { n_dot_l = 0.0f; }                         // choose max { 0, n_dot_l }
    vec3 diffuse = n_dot_l * intensity;                             // scale intensity accordingly

    // phong shading component
    vec3 r = (2 * n_dot_l * ourNorm) - l;                           // compute r (reflected according to snell's law)
    vec3 e = normalize(-1 * ourPos);                                // normalize vector looking at the origin
    float e_dot_r = dot(e, r);                                      // compute dot product
    if (e_dot_r < 0.0f) { e_dot_r = 0.0f; }                         // choose max { 0, e_dot_r }
    float p = pow(e_dot_r, power);                                  // put dot product to the power of p
    vec3 phong = p * intensity;                                     // compute phong component

    // compute paint color
    vec3 paint = (ourColor * (ambient + diffuse)) + phong;

    // clamp paint between 0 and 1
    if (paint.x < 0.0f) { paint.x = 0.0f; }    if (paint.x > 1.0f) { paint.x = 1.0f; }
    if (paint.y < 0.0f) { paint.y = 0.0f; }    if (paint.y > 1.0f) { paint.y = 1.0f; }
    if (paint.z < 0.0f) { paint.z = 0.0f; }    if (paint.z > 1.0f) { paint.z = 1.0f; }

    fragColor = vec4(paint, 1.0f);
}
