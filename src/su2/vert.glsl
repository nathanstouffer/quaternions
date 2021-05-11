#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 myColor;
out vec3 myFragPos;

uniform vec2 zvec;
uniform vec2 wvec;

struct Comp {
    float x;
    float y;
};

struct Quat {
    Comp z;
    Comp w;
};

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
    gl_Position = vec4(aPos, 1.0);
    myColor = aColor;
    myFragPos = vec3(aPos);
}
