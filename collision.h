#ifndef __COLLISION_H_
#define __COLLISION_H_

#include <iostream>
#include <cmath>
#include "particle.h"

// functions that detects the collision and that do collision responses
namespace Collisions
{
    // calculates the time in which the particles collide with each other
    double collision_time(const Particle & p1, const Particle & p2);
}

#endif