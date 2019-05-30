#include "particle.h"
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
    std::cout << D << std::endl;

    if(D < 0)  // without a solution
        return -1;
    else if(D == 0)  // one solution
        return (-b) / (2 * a);
    else  // two solutions - returns the smaller number
    {
        double D_sqrt = sqrt(D);
        double t1 = (-b + D_sqrt) / (2 * a);
        double t2 = (-b - D_sqrt) / (2 * a);
        return (t1 < t2 ? t1 : t2);
    }
}