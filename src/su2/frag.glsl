#version 330 core
in vec3 ourColor;
in vec3 ourFragPos;
in vec3 ourNorm;

uniform vec3 light_pos;          // position of the light
uniform vec3 intensity;          // light intensity
uniform vec3 ambient;            // ambient light intensity
uniform vec3 eye;                // position of the viewer

uniform float power;             // power for phong shading calculation

out vec4 fragColor;

void main() {
    // compute diffuse shading
    vec3 l = normalize(light_pos - ourFragPos);                     // vector in direction on the light
    float n_dot_l = dot(ourNorm, l);                                // compute dot product
    if (n_dot_l < 0.0f) { n_dot_l = 0.0f; }                         // choose max { 0, n_dot_l }
    vec3 diffuse = n_dot_l * intensity;                             // scale intensity accordingly

    // phong shading component
    vec3 r = (2 * n_dot_l * ourNorm) - l;                           // compute r (reflected according to snell's law)
    vec3 e = normalize(eye - ourFragPos);                           // normalize vector looking at the origin
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
