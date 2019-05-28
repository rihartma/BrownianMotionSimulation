#include "simulation.h"

// a function that generates random number in a interval <min, max)
int randrange(int min, int max)
{
    int n = rand() % (max-min);
    return n + min;
}

Particle* Simulation::init(int m, int n)  // an initialization of the simulation
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

void Simulation::close(Particle* particles)  // frees memory
{
    delete[] particles;
}

void Simulation::step(Particle* particles, int n)  // the calculation of the new position and vectors of the particles
{
    for(int i = 0; i < n; i++)
    {
        particles[i].setX(particles[i].getX()+particles[i].getVx());
        particles[i].setY(particles[i].getY()+particles[i].getVy());
    }
}

// int main()
// {
//     return 0;
// }