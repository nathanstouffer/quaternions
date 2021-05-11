#ifndef _CSCI441_SHAPE_H_
#define _CSCI441_SHAPE_H_

#include <cstdlib>
#include <vector>
#include <csci441/vector4.h>
#include <iomanip>

template <typename T, typename P, typename C>
/* method to add a vertex with position and color */
void add_vertex(T& coords, const P& x, const P& y, const P& z,
        const C& r, const C& g, const C& b, bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-with_noise*(rand()%150)/100.;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
    coords.push_back(r*noise);
    coords.push_back(g*noise);
    coords.push_back(b*noise);
}

template <typename T, typename P, typename C, typename N>
/* method to add a vertex with position, color, and a normal */
void add_vertex(T& coords,                                      // data
                  const P& px, const P& py, const P& pz,        // position
                      const C& r, const C& g, const C& b,       // color
                        const N& nx, const N& ny, const N& nz,  // normal
                          bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-with_noise*(rand()%150)/100.;
    coords.push_back(px);
    coords.push_back(py);
    coords.push_back(pz);
    coords.push_back(r*noise);
    coords.push_back(g*noise);
    coords.push_back(b*noise);
    coords.push_back(nx);
    coords.push_back(ny);
    coords.push_back(nz);
}

class Shape {
  public:
    // public attribute to store the coordinates
    std::vector<float> coords;

    /* method to return a string version of the shape */
    std::string toString() const {
      std::ostringstream out;
      // set output precision
      std::setprecision(3);
      // loop over values of matrix
      std::cout << this->coords.size() << std::endl;
      for (unsigned int c = 0; c < this->coords.size(); c++) {
        if (c % 27 == 0) { out << std::endl; }
        if (c % 9 == 0) { out << std::endl; }
        out << this->coords[c] << " ";
      }
      out << std::endl;
      return out.str();
    }
};

class DiscoCube : public Shape {
public:
    //std::vector<float> coords;
    DiscoCube() {
      this->coords = {
           // position          // color           // normal
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
           0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
           0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,

           // position          // color           // normal
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

           // position          // color           // normal
          -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

           // position          // color           // normal
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

           // position          // color           // normal
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f,

           // position          // color           // normal
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f
      };
    }

};

class Cylinder : public Shape {
public:

    Cylinder(unsigned int n, float r, float g, float b) {
        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1)%n)*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);

            // add triangle viL, viH, vip1L
            add_vertex(coords, vi_x, vi_y, -h, r, g, b, (float)cos(theta_i), (float)sin(theta_i), 0.0f);
            add_vertex(coords, vi_x, vi_y, h, r, g, b, (float)cos(theta_i), (float)sin(theta_i), 0.0f);
            add_vertex(coords, vip1_x, vip1_y, -h, r, g, b, (float)cos(theta_ip1), (float)sin(theta_ip1), 0.0f);

            // add triangle vip1L, viH, vip1H
            add_vertex(coords, vip1_x, vip1_y, -h, r, g, b, (float)cos(theta_ip1), (float)sin(theta_ip1), 0.0f);
            add_vertex(coords, vi_x, vi_y, h, r, g, b, (float)cos(theta_i), (float)sin(theta_i), 0.0f);
            add_vertex(coords, vip1_x, vip1_y, h, r, g, b, (float)cos(theta_ip1), (float)sin(theta_ip1), 0.0f);

            // add high triangle vi, vip1, 0
            add_vertex(coords, vip1_x, vip1_y, h, r, g, b, 0.0f, 0.0f, 1.0f);
            add_vertex(coords, vi_x, vi_y, h, r, g, b, 0.0f, 0.0f, 1.0f);
            add_vertex(coords, c_x, c_y, h, r, g, b, 0.0f, 0.0f, 1.0f);

            // // add low triangle vi, vip1, 0
            add_vertex(coords, vip1_x, vip1_y, -h, r, g, b, 0.0f, 0.0f, -1.0f);
            add_vertex(coords, c_x, c_y, -h, r, g, b, 0.0f, 0.0f, -1.0f);
            add_vertex(coords, vi_x, vi_y, -h, r, g, b, 0.0f, 0.0f, -1.0f);
        }
    }
};

class Cone : public Shape {
public:

    Cone(unsigned int n, float r, float g, float b) {

        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        float phi = (M_PI / 2) - atan(2*h / radius);

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1))*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);

            // average of the two angles
            double avg_angle = (theta_i + theta_ip1) / 2;

            // add triangle viL, viH, vip1L
            add_vertex(coords, vi_x, vi_y, -h, r, g, b, cos(theta_i)*cos(phi), sin(theta_i)*cos(phi), sin(phi));
            add_vertex(coords, c_x, c_y, h, r, g, b, cos(avg_angle)*cos(phi), sin(avg_angle)*cos(phi), sin(phi));
            add_vertex(coords, vip1_x, vip1_y, -h, r, g, b, cos(theta_ip1)*cos(phi), sin(theta_ip1)*cos(phi), sin(phi));

            // add low triangle vi, vip1, 0
            add_vertex(coords, vip1_x, vip1_y, -h, r, g, b, 0.0f, 0.0f, -1.0f);
            add_vertex(coords, c_x, c_y, -h, r, g, b, 0.0f, 0.0f, -1.0f);
            add_vertex(coords, vi_x, vi_y, -h, r, g, b, 0.0f, 0.0f, -1.0f);
        }
    }
};

class Sphere : public Shape {
    double x(float r, float phi, float theta){
        return r*cos(theta)*sin(phi);
    }

    double y(float r, float phi, float theta){
        return r*sin(theta)*sin(phi);
    }

    double z(float r, float phi, float theta){
        return r*cos(phi);
    }

public:

    Sphere(unsigned int n, float radius, float r, float g, float b) {
        int n_steps = (n%2==0) ? n : n+1;
        double step_size = 2*M_PI / n_steps;

        for (int i = 0; i < n_steps; ++i) {
            for (int j = 0; j < n_steps/2.0; ++j) {
                double phi_i = i*step_size;
                double phi_ip1 = ((i+1)%n_steps)*step_size;
                double theta_j = j*step_size;
                double theta_jp1 = ((j+1)%n_steps)*step_size;

                // vertex i,j
                double vij_x = x(radius, phi_i, theta_j);
                double vij_y = y(radius, phi_i, theta_j);
                double vij_z = z(radius, phi_i, theta_j);
                Vector4 vij_norm(vij_x, vij_y, vij_z, 0.0f);
                vij_norm = vij_norm.normalized();

                // vertex i+1,j
                double vip1j_x = x(radius, phi_ip1, theta_j);
                double vip1j_y = y(radius, phi_ip1, theta_j);
                double vip1j_z = z(radius, phi_ip1, theta_j);
                Vector4 vip1j_norm(vip1j_x, vip1j_y, vip1j_z, 0.0f);
                vip1j_norm = vip1j_norm.normalized();

                // vertex i,j+1
                double vijp1_x = x(radius, phi_i, theta_jp1);
                double vijp1_y = y(radius, phi_i, theta_jp1);
                double vijp1_z = z(radius, phi_i, theta_jp1);
                Vector4 vijp1_norm(vijp1_x, vijp1_y, vijp1_z, 0.0f);
                vijp1_norm = vijp1_norm.normalized();

                // vertex i+1,j+1
                double vip1jp1_x = x(radius, phi_ip1, theta_jp1);
                double vip1jp1_y = y(radius, phi_ip1, theta_jp1);
                double vip1jp1_z = z(radius, phi_ip1, theta_jp1);
                Vector4 vip1jp1_norm(vip1jp1_x, vip1jp1_y, vip1jp1_z, 0.0f);
                vip1jp1_norm = vip1jp1_norm.normalized();

                // add triangle
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b, vij_norm.x(), vij_norm.y(), vij_norm.z());
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, vip1j_norm.x(), vip1j_norm.y(), vip1j_norm.z());
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, vijp1_norm.x(), vijp1_norm.y(), vijp1_norm.z());

                // add triange
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, vijp1_norm.x(), vijp1_norm.y(), vijp1_norm.z());
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b, vip1jp1_norm.x(), vip1jp1_norm.y(), vip1jp1_norm.z());
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, vip1j_norm.x(), vip1j_norm.y(), vip1j_norm.z());
            }
        }
    }
};

class Torus : public Shape {
    double x(float c, float a, float phi, float theta){
        return (c+a*cos(theta))*cos(phi);
    }

    double y(float c, float a, float phi, float theta){
        return (c+a*cos(theta))*sin(phi);
    }

    double z(float c, float a, float phi, float theta){
        return a*sin(theta);
    }

public:

    Torus(unsigned int n, float c, float a, float r, float g, float b) {

        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = .5;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                double phi_i = i*step_size;
                double phi_ip1 = ((i+1)%n)*step_size;
                double theta_j = j*step_size;
                double theta_jp1 = ((j+1)%n)*step_size;

                // vertex i,j
                double vij_x = x(c, a, phi_i, theta_j);
                double vij_y = y(c, a, phi_i, theta_j);
                double vij_z = z(c, a, phi_i, theta_j);
                Vector4 vij_norm(cos(phi_i)*cos(theta_j), sin(phi_i)*cos(theta_j), sin(theta_j), 0);
                vij_norm = vij_norm.normalized();

                // vertex i+1,j
                double vip1j_x = x(c, a, phi_ip1, theta_j);
                double vip1j_y = y(c, a, phi_ip1, theta_j);
                double vip1j_z = z(c, a, phi_ip1, theta_j);
                Vector4 vip1j_norm(cos(phi_ip1)*cos(theta_j), sin(phi_ip1)*cos(theta_j), sin(theta_j), 0);
                vip1j_norm = vip1j_norm.normalized();

                // vertex i,j+1
                double vijp1_x = x(c, a, phi_i, theta_jp1);
                double vijp1_y = y(c, a, phi_i, theta_jp1);
                double vijp1_z = z(c, a, phi_i, theta_jp1);
                Vector4 vijp1_norm(cos(phi_i)*cos(theta_jp1), sin(phi_i)*cos(theta_jp1), sin(theta_jp1), 0);
                vijp1_norm = vijp1_norm.normalized();

                // vertex i+1,j+1
                double vip1jp1_x = x(c, a, phi_ip1, theta_jp1);
                double vip1jp1_y = y(c, a, phi_ip1, theta_jp1);
                double vip1jp1_z = z(c, a, phi_ip1, theta_jp1);
                Vector4 vip1jp1_norm(cos(phi_ip1)*cos(theta_jp1), sin(phi_ip1)*cos(theta_jp1), sin(theta_jp1), 0);
                vip1jp1_norm = vip1jp1_norm.normalized();

                // add triangle
                add_vertex(coords, vij_x, vij_y, vij_z, r, g, b, vij_norm.x(), vij_norm.y(), vij_norm.z());
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, vip1j_norm.x(), vip1j_norm.y(), vip1j_norm.z());
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, vijp1_norm.x(), vijp1_norm.y(), vijp1_norm.z());

                // add triange
                add_vertex(coords, vijp1_x, vijp1_y, vijp1_z, r, g, b, vijp1_norm.x(), vijp1_norm.y(), vijp1_norm.z());
                add_vertex(coords, vip1jp1_x, vip1jp1_y, vip1jp1_z, r, g, b, vip1jp1_norm.x(), vip1jp1_norm.y(), vip1jp1_norm.z());
                add_vertex(coords, vip1j_x, vip1j_y, vip1j_z, r, g, b, vip1j_norm.x(), vip1j_norm.y(), vip1j_norm.z());
            }
        }
    }

};

#endif
