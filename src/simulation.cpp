#include "simulation.h"

Particle* Simulation::init(int m, int n)  // an initialization of the simulation
{
    // allocation of the memory for the particles
    // for m particles(molecules) of the medium
    // and for n big particels floating in the medium(e.g. pollen grains or dust particles etc.)
    Particle* p = new Particle[m + n];

    srand(time(NULL));  // initialization of the random generater

    int limit = Simulation::SURFACE_WIDTH * Simulation::SURFACE_HEIGHT;  // maximum possible number of particles in the system
    int counter = 0;
    // initialization of the Particles that floats in the medium
    int i = 0;
    while(i < n && counter < limit)
    {
        counter++;
        p[i] = Particle(
            RADIUS_OF_PARTICLES,
            MASS_OF_PARTICLES,
            randrange(RADIUS_OF_PARTICLES, SURFACE_WIDTH - RADIUS_OF_PARTICLES),
            randrange(RADIUS_OF_PARTICLES, SURFACE_HEIGHT - RADIUS_OF_PARTICLES),
            0,
            0
            );
        for(int j = 0; j < i; j++)
        {
            if(overlap(p[i], p[j]))
            {
                i--;
                break;
            }
        }
        i++;
    }

    // initialization of the Particles that forms the medium
    double vx;
    double vy;
    i = n;
    while(i < m + n && counter < limit)
    {
        counter++;
        particle_vector(vx, vy);
        p[i] = Particle(
            RADIUS_OF_MEDIUM,
            MASS_OF_MEDIUM,
            randrange(RADIUS_OF_MEDIUM, SURFACE_WIDTH - RADIUS_OF_MEDIUM),
            randrange(RADIUS_OF_MEDIUM, SURFACE_HEIGHT - RADIUS_OF_MEDIUM),
            vx,
            vy
            );
        for(int j = 0; j < i; j++)
        {
            if(overlap(p[i], p[j]))
            {
                i--;
                break;
            }
        }
        i++;
    }

    // Error message
    if(counter >= limit)
    {
        std::cerr << "To many particles were inserted into the system!" << std::endl;
        exit(EXIT_FAILURE);
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

double Simulation::kinetic_energy(Particle* particles, int n)  // calculates the kinetic energy of the system
{
    double energy = 0;
    for(int i = 0; i < n; i++)
    {
        energy += 0.5 * particles[i].mass() * pow(particles[i].getV(), 2);
    }
    return energy;
}

double Simulation::momentum(Particle* particles, int n)  // calculates the momentum of the system
{
    double m = 0;
    for(int i = 0; i < n; i++)
    {
        m += particles[i].mass() * particles[i].getV();
    }
    return m;
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
    int angle = randrange(0, 361);
    double rad = angle*PI/180;
    vx = velocity*cos(rad);
    vy = velocity*sin(rad);
}

// a function that returns the distance between two particles
double distance(const Particle& p1, const Particle& p2)
{
    double dist = sqrt( pow(p1.getX()-p2.getX(), 2) + pow(p1.getY()-p2.getY(), 2) );
    return dist;
}

// a function that checks whether 2 circles overlap each other
bool overlap(const Particle& p1, const Particle& p2)
{
    if(distance(p1, p2) < p1.radius() + p2.radius())
        return true;
    return false;
}
