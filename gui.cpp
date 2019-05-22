#include <SDL2/SDL.h>  // a library for displaying the simulation
#include <iostream>
#include <cmath>  // a library for a pow func

// screen size
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* bm_window = NULL;  // the window for rendering
SDL_Renderer* bm_renderer = NULL;  // the window renderer

bool init_SDL();  // starts up sdl
void close_SDL();  // frees memory and shuts down sdl

// a func that renders a circle
void drawCircle(SDL_Renderer* r, int centreX, int centreY, int radius);

int main(int argc, char* args[])
{
    init_SDL();
    SDL_Delay(4000);
    close_SDL();
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