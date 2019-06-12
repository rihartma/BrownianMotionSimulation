#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <cstdlib>
#include <iostream>
#include "particle.h"

// a definition of the variables and a declaration of the functions that relates the simulation
namespace Simulation
{
    const double RADIUS_OF_MEDIUM = 5;  // the radius of the particles that forms the medium(e.g. a H2O molecule)
    const double RADIUS_OF_PARTICLES = 50;  // the radius of the particles that floats in the medium(e.g. pollen grain)
    const double MASS_OF_MEDIUM = PI * pow(RADIUS_OF_MEDIUM, 2);  // the mass of the particle that forms the medium(e.g. a H2O molecule)
    const double MASS_OF_PARTICLES = PI * pow(RADIUS_OF_PARTICLES, 2);  // the mass of the particle that floats in the medium(e.g. pollen grain)
    const int NUMBER_OF_MEDIUM = 50;  // the amount of particles that forms the medium(e.g. a H2O molecule)
    const int NUMBER_OF_PARTICLES = 1;  // the number of the particles that floats in the medium(e.g. pollen grain)
    const double MAX_SPEED = 3;  // a maximal possible speed of the particle after the start of the simulation
    const double MIN_SPEED = 0;  // a minimal possible speed of the particle after the start of the simulation
    const int SURFACE_WIDTH = 640;  // width of the surface for the simulation
    const int SURFACE_HEIGHT = 480;  // height of the surface for the simulation

    Particle* init(int m = NUMBER_OF_MEDIUM, int n = NUMBER_OF_PARTICLES);  // an initialization of the simulation
    void close(Particle* particles);  // frees memory
    void step(Particle* particles, int n = NUMBER_OF_MEDIUM + NUMBER_OF_PARTICLES, double t = 1);  // the calculation of the new position and vectors of the particles in time t

    double kinetic_energy(Particle* particles, int n = NUMBER_OF_MEDIUM + NUMBER_OF_PARTICLES);  // calculates the kinetic energy of the system
    double momentum(Particle* particles, int n = NUMBER_OF_MEDIUM + NUMBER_OF_PARTICLES);  // calculates the momentum of the system
}

// a function that generates random number in a interval <min, max)
int randrange(int min, int max);
// a function that generates random vector for velocity and direction representation of the particle
void particle_vector(double& vx, double& vy, int min_velocity = Simulation::MIN_SPEED, int max_velocity = Simulation::MAX_SPEED);

#endif