#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "defs.h"
#include "logic.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game) {
    if(x>=CELL_SIZE && x<=SCREEN_WIDTH-CELL_SIZE && y>=CELL_SIZE && y<=SCREEN_HEIGHT-CELL_SIZE)
    {
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
    }

}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Tictactoe game;
    game.init();
    graphics.render(game);

    int x, y;
    SDL_Event event;
    bool quit = false;
    while (! quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 quit = true;
                 break;

            case SDL_MOUSEBUTTONDOWN:
                 SDL_GetMouseState(&x, &y);
                 int clickedCol = (x - BOARD_X) / CELL_SIZE;
                 int clickedRow = (y - BOARD_Y) / CELL_SIZE;
                 if(game.board[clickedRow][clickedCol] == EMPTY_CELL && x>=CELL_SIZE && x<=SCREEN_WIDTH-CELL_SIZE && y>=CELL_SIZE && y<=SCREEN_HEIGHT-CELL_SIZE)
                 {
                     Mix_PlayChannel( -1, graphics.gClick, 0 );
                 }
                 processClick(x, y, game);
                 graphics.render(game);
                 break;
        }
        switch( event.key.keysym.sym )
        {
            case SDLK_p:
                if( Mix_PlayingMusic() == 0 )
                    {
                        Mix_PlayMusic( graphics.gMusic, -1 );
                    }
                else
                    {
                        if( Mix_PausedMusic() == 1 )
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                    break;

            case SDLK_s:
            Mix_HaltMusic();
            break;
        }
        SDL_Delay(10);
    }

    graphics.quit();
    return 0;
}
