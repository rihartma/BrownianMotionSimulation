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
        // bool flag
        // true - particle p1 collides with the wall
        // false - no collision with walls, collision between p1 and p2 particles
        bool v_wall; // for the left or the right wall(vertical)
        bool h_wall; // for the top or the bottom wall(horizontal)
        // indexes of the particles
        int p1;
        int p2;
        // a collision time
        double t;
    };
    // calculates the time in which the particles collide with each other
    double collision_time(const Particle & p1, const Particle & p2);
    // calculates the time in which tha particle collide with a wall
    c_time wall_collision_time(const Particle & p1, int area_width, int area_height);
    // recalculates the vectors of the particles after a collision appears
    void handle_collision(Particle & p1, Particle & p2);
    // recalculates the vectors of the particles after a collision with wall appear
    void handle_wall_collision(Particle & p, bool h_wall, bool v_wall);
    // finds two particles of p with the nearest collision
    // returns their indexes and collision time
    c_time next_collision(Particle* p, int n, int area_width, int area_height);
}

#endif