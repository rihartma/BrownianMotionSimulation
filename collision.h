#ifndef __COLLISION_H_
#define __COLLISION_H_

#include <iostream>
#include <cmath>
#include <cfloat>
#include "particle.h"

const double PI =  3.14159265359;

// namespace for functions and data types for:
// - the detection of the collisions
// - the collision responses
namespace Collisions
{
    // saves the type of the collision, time of the collision and indexes of the colliding particles
    struct c_time
    {
        // bool flags v_wall
        // true - particle p1 collides with the vertical(left or right) wall
        // false - no collision with vertical wall
        bool v_wall;
        // bool flags v_wall
        // true - particle p1 collides with the horizontal(top of bottom) wall
        // false - no collision with horizontal wall
        bool h_wall;
        // indexes of the particles
        int p1;
        int p2;  // only if both values(h_wall, v_wall) are false - collision of 2 particles
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
    // finds the nearest collision
    c_time next_collision(Particle* p, int n, int area_width, int area_height);
}

#endif