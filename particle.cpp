#include "particle.h"

Particle::Particle()
{
    r = 1;
    m = 1;
    x = 0;
    y = 0;
    vx = 0;
    vy = 1;
}

Particle::Particle(double radius, double mass, double x_pos, double y_pos, double vector_x, double vector_y)
{
    r = radius;
    m = mass;
    x = x_pos;
    y = y_pos;
    vx = vector_x;
    vy = vector_y;
}

Particle::~Particle()
{
}