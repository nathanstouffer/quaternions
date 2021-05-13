#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNorm;

uniform mat4 projection;

uniform vec2 zvec;
uniform vec2 wvec;

out vec3 ourColor;
out vec3 ourFragPos;
out vec3 ourNorm;

struct Comp { float x, y; };
struct Quat { Comp z, w; };

float modulus(Comp c)       { return sqrt(c.x*c.x + c.y*c.y); }
Comp neg(Comp c)            { return Comp(-c.x, -c.y); }
Comp conj(Comp c)           { return Comp(c.x, -c.y); }
Comp mult(Comp c1, Comp c2) { return Comp(c1.x*c2.x - c1.y*c2.y, c1.x*c2.y + c1.y*c2.x); }
Comp plus(Comp c1, Comp c2) { return Comp(c1.x+c2.x, c1.y+c2.y); }

Quat mult(Quat q1, Quat q2) {
    Comp z = plus(mult(q1.z, q2.z), mult(q1.w, neg(conj(q2.w))));
    Comp w = plus(mult(q1.z, q2.w), mult(q1.w, conj(q2.z)));
    return Quat(z, w);
}

void main() {
    Comp z = Comp(zvec.x, zvec.y);
    Comp w = Comp(wvec.x, wvec.y);

    Quat A     = Quat(z, w);
    Quat A_inv = Quat(conj(z), neg(w));
    Quat B     = Quat(Comp(0.0, aPos.x),  Comp(aPos.y,  aPos.z));
    Quat N     = Quat(Comp(0.0, aNorm.x), Comp(aNorm.y, aNorm.z));

    // compute transformed point
    Quat model_prod = mult(A, B);
    model_prod = mult(model_prod, A_inv);
    vec4 model_pos = vec4(model_prod.z.y, model_prod.w.x, model_prod.w.y, 1.0);

    // compute transformed norm
    Quat norm_prod = mult(A, N);
    norm_prod = mult(norm_prod, A_inv);
    vec4 norm_pos = vec4(norm_prod.z.y, norm_prod.w.x, norm_prod.w.y, 1.0);

    // set the output variables
    gl_Position = projection * model_pos;
    ourColor    = aColor;
    ourFragPos  = vec3(model_pos);
    ourNorm     = vec3(norm_pos);
}
