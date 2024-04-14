#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

#define TRUE 1
#define FALSE 0
#define FPS 60
#define FRAME_DELAY (1000 / FPS)

int last_frame_ticks = 0;

typedef struct
{
    int x, y, speedx, speedy;
} Particle;

Particle particle = {WIDTH / 2, HEIGHT / 2, 130, 130};

int is_running = 0;
SDL_Window *window;
SDL_Renderer *renderer;

int initialize_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return FALSE;
    }

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
    {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

int destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void setup()
{
    // Setup effect
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        is_running = FALSE;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            is_running = FALSE;
        }
        break;
    default:
        break;
    }
}

void update()
{
    // Have consistent FPS wasting some time since last render
    int time_to_wait = FRAME_DELAY - (SDL_GetTicks() - last_frame_ticks);

    // If we stiil have time to wait, delay next render
    if(time_to_wait > 0 && time_to_wait <= FRAME_DELAY) {
        SDL_Delay(time_to_wait);
    }

    // Time based factor for handling time evolution.
    // Having this approach we do not need to delay on every fps as all evolutions
    // are time based and depepnded on FPS.
    float delta_time = (SDL_GetTicks() - last_frame_ticks) / 1000.0f;
    last_frame_ticks = SDL_GetTicks();

    particle.x += particle.speedx * delta_time;
    particle.y += particle.speedy * delta_time;
    if (particle.x <= 0 || particle.x >= WIDTH)
    {
        particle.speedx = -particle.speedx;
    }
    if (particle.y <= 0 || particle.y >= HEIGHT)
    {
        particle.speedy = -particle.speedy;
    }
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, particle.x, particle.y);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    is_running = initialize_window();

    while (is_running)
    {
        process_input();
        update();
        draw(renderer);
    }

    destroy_window();

    return 0;
}