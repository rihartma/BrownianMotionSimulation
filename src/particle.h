#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <cmath>  // for the unit vector calculation

const double PI =  3.14159265359;

// declaration of a class representing every particle
// e.g. pollen grain, dust particle, H2O molecule or O2 molecule etc.
class Particle
{
private:
    // radius of the particle
    double r;
    // mass of the particle
    double m;
    // position of the particle
    double x;
    double y;
    // a vector of the particle - representation of the movement direction and the velocity
    double vx;
    double vy;
public:
    Particle();
    Particle(double radius, double mass, double x_pos, double y_pos, double vector_x, double vector_y);
    
    // working with the position
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double new_x) { x = new_x; }
    void setY(double new_y) { y = new_y; }

    // working with the vector
    double getVx() const { return vx; }
    double getVy() const { return vy; }
    void setVx(double new_vx) { vx = new_vx; }
    void setVy(double new_vy) { vy = new_vy; }

    // returns the velocity - size of the vector (vx, vy)
    double getV() const { return sqrt(pow(vx, 2) + pow(vy, 2)); }

    double radius() const { return r; }  // returns the radius of the particle
    double mass() const { return m; }  // returns the mass of the particle

    ~Particle();
};

#endif