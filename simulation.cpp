#include <cstdlib>  // a library for random nums
#include <iostream>
#include "particle.h"

const int RADIUS_OF_MEDIUM = 5;  // the radius of the particles that forms the medium(e.g. a H2O molecule)
const int RADIUS_OF_PARTICLES = 50;  // the radius of the particles that floats in the medium(e.g. pollen grain)
const int MASS_OF_MEDIUM = 1;  // the mass of the particle that forms the medium(e.g. a H2O molecule)
const int MASS_OF_PARTICLES = 10;  // the mass of the particle that floats in the medium(e.g. pollen grain)
const int MAX_SPEED = 5;  // a maximal possible speed of the particle after the start of the simulation
const int MIN_SPEED = 1;  // a minimal possible speed of the particle after the start of the simulation
const int SURFACE_WIDTH = 640;  // width of the surface for the simulation
const int SURFACE_HEIGHT = 480;  // height of the surface for the simulation

int randrange(int min, int max)  // a function that generates random number in a interval <min, max)
{
    int n = rand() % (max-min);
    return n + min;
}

Particle* init(int m, int n = 1)  // an initialization of the simulation
{
    // allocation of the memory for the particles
    // for m particles(molecules) of the medium
    // and for n big particels floating in the medium(e.g. pollen grains or dust particles etc.)
    Particle* p = new Particle[m + n];

    srand(time(NULL));  // initialization of the random generater
    // initialization of the Particles that forms the medium
    for(int i = 0; i < m; i++)
    {
        p[i] = Particle(
            RADIUS_OF_MEDIUM,
            MASS_OF_MEDIUM,
            randrange(MIN_SPEED, MAX_SPEED),
            randrange(RADIUS_OF_MEDIUM, SURFACE_HEIGHT - RADIUS_OF_MEDIUM),
            randrange(RADIUS_OF_MEDIUM, SURFACE_WIDTH - RADIUS_OF_MEDIUM),
            randrange(0, SURFACE_WIDTH),
            randrange(0, SURFACE_HEIGHT)
            );
    }
    // initialization of the Particles that floats in the medium
    for(int i = m; i < m + n; i++)
    {
        p[i] = Particle(
            RADIUS_OF_PARTICLES,
            MASS_OF_PARTICLES,
            0,
            randrange(RADIUS_OF_PARTICLES, SURFACE_HEIGHT - RADIUS_OF_PARTICLES),
            randrange(RADIUS_OF_PARTICLES, SURFACE_WIDTH - RADIUS_OF_PARTICLES),
            0,
            1
            );
    }

    return p;
}

void close(Particle* particles)  // frees memory
{
    delete[] particles;
}

Particle* step(Particle* particles)  // the calculation of the new position and vectors of the particles
{
}

int main()
{
    return 0;
}