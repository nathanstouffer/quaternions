#ifndef _COMP_MTX2_H_
#define _COMP_MTX2_H_

#include <complex>
#include <cmath>

typedef std::complex<float> compf;

class CompMtx2 {
private:

    compf dot(const compf* m1, unsigned int row, const compf* m2, int col) const {
        compf dot(0.0, 0.0);
        for (int i = 0; i < 2; ++i) {
            dot += m1[idx(row,i)]*m2[idx(i,col)];
        }
        return dot;
    }

    void mult(compf* target, const compf* const m1, const compf* const m2) const {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                target[idx(i,j)] = dot(m1, i, m2, j);
            }
        }
    }

    unsigned int idx(unsigned int r, unsigned int c) const {
        return r + c*2;
    }

public:
    compf values [4];

    // identity constructor
    CompMtx2 () { this->setToId(); }

    // constructor with preset array
    CompMtx2(compf vals[4]) {
        int v;
        for (v = 0; v < 4; v++) { this->values[v] = vals[v]; }
    }

    void setToId() {
        this->values[idx(0,0)] = compf(1.0, 0.0);      this->values[idx(0,1)] = compf(0.0, 0.0);
        this->values[idx(1,0)] = compf(0.0, 0.0);      this->values[idx(1,1)] = compf(1.0, 0.0);
    }

    CompMtx2 scaled(compf scalar) {
        compf vals [4];
        int v;
        for (v = 0; v < 4; v++) {
            vals[v] = scalar*this->values[v];
        }
        return CompMtx2(vals);
    }

    compf det() {
        return values[idx(0,0)]*values[idx(1,1)] - values[idx(1,0)]*values[idx(0,1)];
    }

    CompMtx2 inv(){
        compf vals [4];
        // edit the contents of vals
        vals[idx(0,0)] =  this->values[idx(1,1)];   vals[idx(0,1)] = -this->values[idx(0,1)];
        vals[idx(1,0)] = -this->values[idx(1,0)];   vals[idx(1,1)] =  this->values[idx(0,0)];

        compf det = this->det();
        int v;
        for (v = 0; v < 4; v++) { vals[v] /= det; }
        return CompMtx2(vals);
    }

    CompMtx2 transpose(){
        compf vals [4];
        // edit the contents of vals
        vals[idx(0,0)] = this->values[idx(0,0)];   vals[idx(0,1)] = this->values[idx(1,0)];
        vals[idx(1,0)] = this->values[idx(0,1)];   vals[idx(1,1)] = this->values[idx(1,1)];
        return CompMtx2(vals);
    }

    CompMtx2 conjugate(){
        compf vals [4];
        // edit the contents of vals
        vals[idx(0,0)] = std::conj(this->values[idx(1,1)]);   vals[idx(0,1)] = std::conj(this->values[idx(1,0)]);
        vals[idx(1,0)] = std::conj(this->values[idx(1,0)]);   vals[idx(1,1)] = std::conj(this->values[idx(0,0)]);
        return CompMtx2(vals);
    }

    CompMtx2 operator*(const CompMtx2& m) const {
        CompMtx2 ret;
        mult(ret.values, values, m.values);
        return ret;
    }

    void set(int r, int c, compf val) { this->values[idx(r, c)] = val; }
    compf operator()(int row, int col) const {
        return this->values[idx(row, col)];
    }

};

#endif
