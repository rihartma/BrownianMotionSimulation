#include "collision.h"

// calculates the time in which the particles collide with each other
double Collisions::collision_time(const Particle & p1, const Particle & p2)
{
    // a difference between the vectors of the particles
    double vx = p1.getVx() - p2.getVx();
    double vy = p1.getVy() - p2.getVy();
    // a difference between the coordinates of the centers of the particles
    double dx = p1.getX() - p2.getX();
    double dy = p1.getY() - p2.getY();
    // counts a, b, c - the parametres for a quadratic equation
    // a = v*v
    double a = vx*vx + vy*vy;
    if(a == 0)  // p1 and p2 has got the same vector, cannot calculate with a quadratic equation
    {
        if((dx*dx + dy*dy) == pow(p1.radius(), 2) + pow(p2.radius(), 2))  // they are colliding
            return 0;
        else
            return -1;  // never collides( or they are overlaping each other )
    }
    // b = 2*d*v
    double b = 2 * (dx*vx + dy*vy);
    // c = d*d - (radius1 + radius2)^2
    double c = dx*dx + dy*dy - pow(p1.radius() + p2.radius(), 2);
    // a discriminant
    double D = b*b - 4*a*c;

    if(D < 0)  // without a solution
        return -1;
    else if(D == 0)  // one solution
        return (-b) / (2 * a);
    else  // two solutions - returns the smaller number
    {
        double D_sqrt = sqrt(D);
        double t1 = (-b + D_sqrt) / (2 * a);
        double t2 = (-b - D_sqrt) / (2 * a);
        if(t1 >= 0 && t2 >= 0)
            return (t1 < t2 ? t1 : t2);    
        else if(t1 >= 0)
            return t1;
        else if(t2 >= 0)
            return t2;
        else
            return -1;
    }
}

// recalculates the vectors of the particles after a collision appears
void Collisions::handle_collision(Particle & p1, Particle & p2)
{
    double p1_m = p1.mass(); // a mass of the p1 particle
    double p2_m = p2.mass(); // a mass of the p2 particle
    // a unit vector with direction same as the line connecting the centers of the particles
    double r_size = sqrt(pow(p2.getX()-p1.getX(), 2) + pow(p2.getY()-p1.getY(), 2));
    double rx = (p2.getX()-p1.getX()) / r_size;
    double ry = (p2.getY()-p1.getY()) / r_size;
    // recalculating the coordinates into a rotated coordinate system
    // a vector (rx, ry) represents x-axis
    double p1vx = p1.getVx() * rx + p1.getVy() * ry;
    double p1vy = - p1.getVx() * ry + p1.getVx() * rx;
    double p2vx = p2.getVx() * rx + p2.getVy() * ry;
    double p2vy = - p2.getVx() * ry + p2.getVx() * rx;
    // recalculation of x-components of the vectors
    // conservates the momentum and kinetic energy
    double new_p1vx = p1vx * (p1_m - p2_m) / (p1_m + p2_m) + p2vx * 2 * p2_m / (p1_m + p2_m);
    double new_p2vx = p1vx * 2 * p1_m / (p1_m + p2_m) + p2vx * (p2_m - p1_m) / (p1_m + p2_m);
    // sets the new vectors(rotated back to normal coordinate system)
    p1.setVx(new_p1vx * rx - p1vy * ry);
    p1.setVy(new_p1vx * ry + p1vy * rx);
    p2.setVx(new_p2vx * rx - p2vy * ry);
    p2.setVy(new_p2vx * ry + p2vy * rx);
}

// finds two particles of p with the nearest collision
// returns their indexes and collision time
Collisions::c_time Collisions::next_collision(Particle* p, int n)
{
    Collisions::c_time result;
    result.p1 = 0;
    result.p2 = 0;
    result.t = DBL_MAX;
    double t;
    // goes through every possible option
    for(int i = 0; i < n-1; i++)
    {
        for(int y = i+1; y < n; y++)
        {
            t = Collisions::collision_time(p[i], p[y]);
            if(t < 0)
                continue;
            if(t < result.t)
            {
                result.p1 = i;
                result.p2 = y;
                result.t = t;
            }
        }
    }
    return result;
}