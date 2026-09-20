#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int SDLCALL gbemulator_runapp_callback(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    return SDL_RunApp(argc, argv, gbemulator_runapp_callback, NULL);
}

int SDLCALL gbemulator_runapp_callback(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }

    printf("GBEmulator started!\n");

    SDL_Quit();

    return 0;
}