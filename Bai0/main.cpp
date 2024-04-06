#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

int screen_width=800;
int screen_height=600;
char* screen_title="bang ve";

int main(int argc, char *argv[])
{
    SDL_Window* window = intitSDL(screen_width, screen_height, screen_title);
    SDL_Renderer* renderer = CreateRenderer(window);

    SDL_RenderClear(renderer);



    return 0;
}

