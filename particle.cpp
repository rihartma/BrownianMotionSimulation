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

Particle::Particle(double radius, double mass, double velocity, double x_pos, double y_pos, double vector_x, double vector_y)
{
    r = radius;
    m = mass;
    v = velocity;
    x = x_pos;
    y = y_pos;

    // a conversion to the unit vector
    double size = sqrt(pow(vector_x, 2) + pow(vector_y, 2));
    vx = vector_x / size;
    vy = vector_y / size;
}

Particle::~Particle()
{
}