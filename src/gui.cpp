#include <SDL2/SDL.h>  // a library for displaying the simulation
#include <iostream>
#include <cmath>
#include <chrono>
#include "particle.h"
#include "simulation.h"
#include "collision.h"

// screen size
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// delay between rendering new frames
const int DELAY = 25;

SDL_Window* bm_window = NULL;  // the window for rendering
SDL_Renderer* bm_renderer = NULL;  // the window renderer

bool init_SDL();  // starts up sdl
void close_SDL();  // frees memory and shuts down sdl

void drawCircle(SDL_Renderer* r, int centreX, int centreY, int radius);  // a func that renders a circle
void draw_scene(SDL_Renderer* r, Particle* p, int n = Simulation::NUMBER_OF_MEDIUM + Simulation::NUMBER_OF_PARTICLES);  // renders every particle

// a func that runs the simulation
void run();

int main(int argc, char* args[])
{
    run();
    return 0;
}

bool init_SDL()
{
    // Initialization of SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cerr << "SDL could not initialize! SDL_Error: " 
                << SDL_GetError()
                << std::endl;
        return false;
    }
    else
    {
        // creates a window
        bm_window = SDL_CreateWindow("Brownian Motion Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( bm_window == NULL )
        {
            std::cerr << "Window could not be created! SDL_Error: "
                    << SDL_GetError()
                    << std::endl;
            return false;
        }
        // creates a renderer
        bm_renderer = SDL_CreateRenderer(bm_window, -1, SDL_RENDERER_ACCELERATED);
        if( bm_renderer == NULL )
        {
            std::cerr << "Renderer could not be created! SDL Error: "
                    << SDL_GetError()
                    << std::endl;
            return false;
        }
        SDL_SetRenderDrawColor(bm_renderer, 255, 255, 255, 255);
        SDL_RenderClear(bm_renderer);
        SDL_RenderPresent(bm_renderer);
    }
    return true;
}

void close_SDL()
{
    // destroy window
    SDL_DestroyRenderer(bm_renderer);
    bm_renderer = NULL;
    SDL_DestroyWindow(bm_window);
    bm_window = NULL;
    // shuts down SDL subsystems
    SDL_Quit();
}

// the implementation of the Mid-Point Circle Drawing Algorithm
void drawCircle(SDL_Renderer* r, int centreX, int centreY, int radius)
{
    int x = 0;
    int y = radius;
    while ( x <= y )
    {
        SDL_RenderDrawPoint(r, centreX + x, centreY - y);
        SDL_RenderDrawPoint(r, centreX + x, centreY + y);
        SDL_RenderDrawPoint(r, centreX - x, centreY - y);
        SDL_RenderDrawPoint(r, centreX - x, centreY + y);
        SDL_RenderDrawPoint(r, centreX + y, centreY - x);
        SDL_RenderDrawPoint(r, centreX + y, centreY + x);
        SDL_RenderDrawPoint(r, centreX - y, centreY - x);
        SDL_RenderDrawPoint(r, centreX - y, centreY + x);

        x++;
        if (pow(x+1, 2) + pow(y-0.5, 2) >= pow(radius, 2))
            y--;
    }
}

// draws the actual scene
void draw_scene(SDL_Renderer* r, Particle* p, int n)
{
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderClear(r);
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    for(int i = 0; i < n; i++)
    {
        drawCircle(r, p[i].getX(), p[i].getY(), p[i].radius());
    }
    SDL_RenderPresent(r);
}

// runs the simulation
void run()
{
    init_SDL();

    // An event initialization for the quit button
    SDL_Event event;
    bool quit = false;

    Particle* particles = Simulation::init();

    // Initialization of the varibles for mesuring of the execution time
    // Synchronizes the steps with a longer execution time(More collisions in a small interval)
    std::chrono::high_resolution_clock::time_point measure_t_1;
    std::chrono::high_resolution_clock::time_point measure_t_2;
    int duration;
    
    // Size of the step of a one time unit
    double step = 1;
    double part_step = step;

    // Stores the information of the nearest collision
    Collisions::c_time next_col;
    next_col = Collisions::next_collision(particles, Simulation::NUMBER_OF_MEDIUM + Simulation::NUMBER_OF_PARTICLES, Simulation::SURFACE_WIDTH, Simulation::SURFACE_HEIGHT);

    // a main loop
    while(!quit)
    {
        // std::cout << "Energy: " << Simulation::kinetic_energy(particles) << ", momentum: " << Simulation::momentum(particles) << std::endl;
        
        // drawing of the simulation between the collisions
        while(next_col.t - part_step >= 0)
        {
            measure_t_1 = std::chrono::high_resolution_clock::now();
            next_col.t = next_col.t - part_step;
            Simulation::step(particles, Simulation::NUMBER_OF_MEDIUM + Simulation::NUMBER_OF_PARTICLES, part_step);
            draw_scene(bm_renderer, particles);
            measure_t_2 = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(measure_t_2 - measure_t_1).count();
            SDL_Delay((DELAY-duration/1000));
            part_step = step;
        }
        // calculates the next collision and does the collision responses
        measure_t_1 = std::chrono::high_resolution_clock::now();
        do
        {
            Simulation::step(particles, Simulation::NUMBER_OF_MEDIUM + Simulation::NUMBER_OF_PARTICLES, next_col.t);
            part_step -= next_col.t;
            // does the collision response
            if(next_col.h_wall || next_col.v_wall)
                Collisions::handle_wall_collision(particles[next_col.p1], next_col.h_wall, next_col.v_wall);
            else
                Collisions::handle_collision2(particles[next_col.p1], particles[next_col.p2]);
            next_col = Collisions::next_collision(particles, Simulation::NUMBER_OF_MEDIUM + Simulation::NUMBER_OF_PARTICLES, Simulation::SURFACE_WIDTH, Simulation::SURFACE_HEIGHT);
        }
        while(part_step - next_col.t >= 0);
        measure_t_2 = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(measure_t_2 - measure_t_1).count();
        SDL_Delay(abs(DELAY-duration/1000));

        // Checking if a quitbutton was or wasn't pressed
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
                quit = true;
        }
    }
    // shuts down the simulation
    Simulation::close(particles);
    close_SDL();
}