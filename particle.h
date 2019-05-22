#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// declaration of a class representing every particle
// e.g. pollen grain, dust particle, H2O molecule or O2 molecule etc.
class Particle
{
private:
    // radius of the particle
    int r;
    // mass of the particle
    int m;
    // position of the particle
    int x;
    int y;
    // vector representing speed and direction of the particle
    int vx;
    int vy;
public:
    Particle();
    Particle(int radius, int mass, int x_pos, int y_pos, int vector_x, int vector_y);
    ~Particle();
};

#endif