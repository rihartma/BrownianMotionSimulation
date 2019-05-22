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
    // speed of the particle
    float v;
    // position of the particle
    int x;
    int y;
    // unit vector of the particle - representation of the movement direction
    int vx;
    int vy;
public:
    Particle();
    Particle(int radius, int mass, int x_pos, int y_pos, int vector_x, int vector_y);
    
    // working with the position
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int new_x) { x = new_x; }
    void setY(int new_y) { y = new_y; }

    // working with the vector
    int getVx() const { return vx; }
    int getVy() const { return vy; }
    void setVx(int new_vx) { vx = new_vx; }
    void setVy(int new_vy) { vy = new_vy; }

    // working with the velocity
    float getV() const { return v; }
    void setV(int new_v) { v = new_v; }

    int radius() const { return r; }  // returns the radius of the particle
    int mass() const { return m; }  // returns the mass of the particle

    ~Particle();
};

#endif