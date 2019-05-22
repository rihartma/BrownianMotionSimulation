#include "particle.h"

Particle::Particle()
{
    r = 1;
    m = 1;
    v = 1;
    x = 0;
    y = 0;
    vx = 0;
    vy = 1;
}

Particle::Particle(int radius, int mass, int velocity, int x_pos, int y_pos, int vector_x, int vector_y)
{
    r = radius;
    m = mass;
    v = velocity;
    x = x_pos;
    y = y_pos;
    vx = vector_x;
    vy = vector_y;
}

Particle::~Particle()
{
}