#ifndef _SU2_QUAT_H_
#define _SU2_QUAT_H_

#include <csci441/vector4.h>

#include "compmtx2.cpp"

typedef std::complex<float> compf;

class SU2Quat {
    private:


    public:
        CompMtx2 mtx;

        // identity quaternion constructor
        SU2Quat() { this->mtx.setToId(); }
        SU2Quat(CompMtx2 p_mtx) { this->mtx = p_mtx; }

        SU2Quat (float theta, Vector4 axis) {
            axis = axis.normalized();
            float c = std::cos(theta/2);        // compute sin and cos of theta/2
            float s = std::sin(theta/2);
            this->mtx = CompMtx2();
            this->mtx.set(0, 0, compf(s,          -s*axis.z()));      this->mtx.set(0, 1, compf(s*axis.y(), -s*axis.x()));
            this->mtx.set(1, 0, compf(s*axis.y(), -s*axis.x()));      this->mtx.set(1, 1, compf(s,           s*axis.z()));
        }


        SU2Quat normalized() {
            compf det = this->mtx.det();
            return SU2Quat(this->mtx.scaled(compf(1.0, 0.0)/det));
        }

        SU2Quat inv() { return SU2Quat(this->mtx.conjugate().transpose()); }
        SU2Quat operator*(const SU2Quat& m) const {
            return SU2Quat(this->mtx * m.mtx);
        }



};

#endif
