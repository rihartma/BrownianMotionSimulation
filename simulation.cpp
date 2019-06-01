#include "simulation.h"

Particle* Simulation::init(int m, int n)  // an initialization of the simulation
{
    // allocation of the memory for the particles
    // for m particles(molecules) of the medium
    // and for n big particels floating in the medium(e.g. pollen grains or dust particles etc.)
    Particle* p = new Particle[m + n];

    srand(time(NULL));  // initialization of the random generater
    // initialization of the Particles that forms the medium
    double vx;
    double vy;
    for(int i = 0; i < m; i++)
    {
        particle_vector(vx, vy);
        p[i] = Particle(
            RADIUS_OF_MEDIUM,
            MASS_OF_MEDIUM,
            randrange(RADIUS_OF_MEDIUM, SURFACE_WIDTH - RADIUS_OF_MEDIUM),
            randrange(RADIUS_OF_MEDIUM, SURFACE_HEIGHT - RADIUS_OF_MEDIUM),
            vx,
            vy
            );
    }
    // initialization of the Particles that floats in the medium
    for(int i = m; i < m + n; i++)
    {
        p[i] = Particle(
            RADIUS_OF_PARTICLES,
            MASS_OF_PARTICLES,
            randrange(RADIUS_OF_PARTICLES, SURFACE_WIDTH - RADIUS_OF_PARTICLES),
            randrange(RADIUS_OF_PARTICLES, SURFACE_HEIGHT - RADIUS_OF_PARTICLES),
            0,
            0
            );
    }

    return p;
}

void Simulation::close(Particle* particles)  // frees memory
{
    delete[] particles;
}

void Simulation::step(Particle* particles, int n, double t)  // the calculation of the new position and vectors of the particles in time t
{
    for(int i = 0; i < n; i++)
    {
        particles[i].setX(particles[i].getX()+particles[i].getVx()*t);
        particles[i].setY(particles[i].getY()+particles[i].getVy()*t);
    }
}

// a function that generates random number in a interval <min, max)
int randrange(int min, int max)
{
    int n = rand() % (max-min);
    return n + min;
}
// a function that generates random vector for velocity and direction representation of the particle
void particle_vector(double& vx, double& vy, int min_velocity, int max_velocity)
{
    int velocity = randrange(min_velocity, max_velocity + 1);
    vx = randrange(0, velocity + 1);
    vy = sqrt(pow(velocity, 2) - pow(vx, 2));
}


// int main()
// {
//     return 0;
// }