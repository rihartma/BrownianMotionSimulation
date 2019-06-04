#ifndef __COLLISION_H_
#define __COLLISION_H_

#include <iostream>
#include <cmath>
#include <cfloat>
#include "particle.h"

const double PI =  3.14159265359;

// functions that detects the collision and that do collision responses
namespace Collisions
{
    struct c_time  // saves to indexes of the particles and time t in which the particles gonna collide
    {
        // indexes of the particles
        int p1;
        int p2;
        // a collision time
        double t;
    };
    // calculates the time in which the particles collide with each other
    double collision_time(const Particle & p1, const Particle & p2);
    // recalculates the vectors of the particles after a collision appears
    void handle_collision(Particle & p1, Particle & p2);
    // finds two particles of p with the nearest collision
    // returns their indexes and collision time
    c_time next_collision(Particle* p, int n);
}

#endif