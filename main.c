#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
    int x, y, speddx, speeddy;
} Particle;

Particle position = {WIDTH / 2, HEIGHT / 2, 1, 1};

void update()
{
    position.x += position.speddx;
    position.y += position.speeddy;
    if(position.x < 0 || position.x > WIDTH)
    {
        position.speddx = -position.speddx;
    }
    if(position.y < 0 || position.y > HEIGHT)
    {
        position.speeddy = -position.speeddy;
    }
}

void draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, position.x, position.y);

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
    {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }

        update();
        draw(renderer);
    }

    return 0;
}