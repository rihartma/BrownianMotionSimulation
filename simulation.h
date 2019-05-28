#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <cstdlib>  // for random numbers
#include <iostream>
#include "particle.h"

// a function that generates random number in a interval <min, max)
int randrange(int min, int max);

// a definition of the variables and a declaration of the functions that relates the simulation
namespace Simulation
{
    const int RADIUS_OF_MEDIUM = 5;  // the radius of the particles that forms the medium(e.g. a H2O molecule)
    const int RADIUS_OF_PARTICLES = 50;  // the radius of the particles that floats in the medium(e.g. pollen grain)
    const int MASS_OF_MEDIUM = 1;  // the mass of the particle that forms the medium(e.g. a H2O molecule)
    const int MASS_OF_PARTICLES = 10;  // the mass of the particle that floats in the medium(e.g. pollen grain)
    const int NUMBER_OF_MEDIUM = 1;  // the amount of particles that forms the medium(e.g. a H2O molecule)
    const int NUMBER_OF_PARTICLES = 0;  // the number of the particles that floats in the medium(e.g. pollen grain)
    const int MAX_SPEED = 5;  // a maximal possible speed of the particle after the start of the simulation
    const int MIN_SPEED = 1;  // a minimal possible speed of the particle after the start of the simulation
    const int SURFACE_WIDTH = 640;  // width of the surface for the simulation
    const int SURFACE_HEIGHT = 480;  // height of the surface for the simulation

    Particle* init(int m = NUMBER_OF_MEDIUM, int n = NUMBER_OF_PARTICLES);  // an initialization of the simulation
    void close(Particle* particles);  // frees memory
    void step(Particle* particles, int n = NUMBER_OF_MEDIUM + NUMBER_OF_PARTICLES);  // the calculation of the new position and vectors of the particles
}

#endif