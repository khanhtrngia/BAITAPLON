#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int width=640;
const int height=480;

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screensurface = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }
    else
    {
        window = SDL_CreateWindow("SDL",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width, height,SDL_WINDOW_SHOWN);
        if(window==nullptr)
        {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError();
        }
        else
        {
            //Get window surface
            screensurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screensurface, NULL, SDL_MapRGB( screensurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while( quit == false )
            {
                while( SDL_PollEvent( &e ) )
                {
                    if( e.type == SDL_QUIT ) quit = true;
                }
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
