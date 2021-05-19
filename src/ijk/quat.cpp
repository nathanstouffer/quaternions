#ifndef _QUAT_H_
#define _QUAT_H_

#include <cmath>

#include <csci441/matrix4.h>
#include <csci441/vector4.h>

class Quat {
    private:
        Vector4 vec;

    public:

        // quaternion constructors
        Quat() { this->set_to_identity(); }
        Quat(Vector4 p_vec) { this->vec = p_vec; }

        Quat (float theta, Vector4 axis) {
            axis.w(0.0f);                         // ensure that the w coordinate is 0
            axis = axis.normalized();
            float c = std::cos(theta/2.0);        // compute sin and cos of theta/2
            float s = std::sin(theta/2.0);
            this->vec = Vector4(c, -s*axis.z(), s*axis.y(), -s*axis.x());
        }

        void set_to_identity() { this->vec = Vector4(1.0f, 0.0f, 0.0f, 0.0f); }

        double norm() { return this->vec.norm(); }

        Quat conj() { return Quat(Vector4(vec.x(), -vec.y(), -vec.z(), -vec.w())); }

        Quat scaled(double s) {
            Vector4 scaled(s*vec.x(), s*vec.y(), s*vec.z(), s*vec.w());
            return Quat(scaled);
        }

        Quat normalized() {
            double norm = this->norm();
            return this->scaled(1/norm);
        }

        Quat inv() {
            double scalar = 1/(this->norm()*this->norm());
            return this->conj().scaled(scalar);
        }

        Quat slerp(Quat q, float t) {
            double phi = std::acos(this->vec.dot(q.vec));
            double s1 = std::sin((1-t)*phi)/std::sin(phi);
            double s2 = std::sin(t*phi)/std::sin(phi);
            Quat q1 = this->scaled(s1);
            Quat q2 = q.scaled(s2);
            return q1 + q2;
        }

        Quat operator+(const Quat& q) const {
            Vector4 sum;
            sum.x(vec.x() + q.x());
            sum.y(vec.y() + q.y());
            sum.z(vec.z() + q.z());
            sum.w(vec.w() + q.w());
            return Quat(sum);
        }

        Quat operator*(const Quat& q) const {
            Vector4 prod;
            prod.x(vec.x()*q.x() - vec.y()*q.y() - vec.z()*q.z() - vec.w()*q.w());
            prod.y(vec.x()*q.y() + vec.y()*q.x() + vec.z()*q.w() - vec.w()*q.z());
            prod.z(vec.x()*q.z() - vec.y()*q.w() + vec.z()*q.x() + vec.w()*q.y());
            prod.w(vec.x()*q.w() + vec.y()*q.z() - vec.z()*q.y() + vec.w()*q.x());
            return Quat(prod);
        }

        Matrix4 to_matrix() {
            Matrix4 rot;
            rot.set(0, 0, x()*x() + y()*y() - z()*z() - w()*w());
            rot.set(0, 1, 2*(z()*y() - w()*x()));
            rot.set(0, 2, 2*(z()*x() + w()*y()));

            rot.set(1, 0, 2*(z()*y() + w()*x()));
            rot.set(1, 1, x()*x() - y()*y() + z()*z() - w()*w());
            rot.set(1, 2, 2*(w()*z() - y()*x()));

            rot.set(2, 0, 2*(w()*y() - z()*x()));
            rot.set(2, 1, 2*(y()*x() + w()*z()));
            rot.set(2, 2, x()*x() - y()*y() - z()*z() + w()*w());
            return rot;
        }

        // GETTER AND OUTPUT METHODS

        float x() const { return this->vec.x(); }
        float y() const { return this->vec.y(); }
        float z() const { return this->vec.z(); }
        float w() const { return this->vec.w(); }

        std::string to_string() const {
            std::ostringstream os;
            os << vec.x() << " "  << vec.y() << "i ";
            os << vec.z() << "j " << vec.z() << "k ";
            return os.str();
        }

        friend std::ostream& operator<<(std::ostream& os, const Quat& q) {
            os << q.to_string();
            return os;
        }

};

#endif
