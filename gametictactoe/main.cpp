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
    SDL_Event event;
    while (true) {
        if ( SDL_PollEvent(&event) != 0 &&
             (event.type == SDL_KEYDOWN || event.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
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

    bool checkWin(char player, Tictactoe& game) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (game.board[i][0] == player && game.board[i][1] == player && game.board[i][2] == player)
                return true;
            if (game.board[0][i] == player && game.board[1][i] == player && game.board[2][i] == player)
                return true;
        }
        if (game.board[0][0] == player && game.board[1][1] == player && game.board[2][2] == player)
            return true;
        if (game.board[0][2] == player && game.board[1][1] == player && game.board[2][0] == player)
            return true;
        return false;
    }

    bool isBoardFull(Tictactoe& game) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (game.board[i][j] == EMPTY_CELL) {
                    return false;
                }
            }
        }
        return true;
    }
void checkGameState(Tictactoe& game, SDL_Renderer* renderer, Graphics& graphic) {
    if (checkWin(X_CELL, game)) {
        SDL_RenderCopy(renderer, graphic.xwin, NULL, NULL);
        graphic.presentScene();
        Mix_PlayChannel( -1, graphic.gEnd, 0 );
        waitUntilKeyPressed();
        game.init();
        graphic.render(game);
    }
    if (checkWin(O_CELL, game)) {
        SDL_RenderCopy(renderer, graphic.owin, NULL, NULL);
        graphic.presentScene();
        Mix_PlayChannel( -1, graphic.gEnd, 0 );
        waitUntilKeyPressed();
        game.init();
        graphic.render(game);
    }
    if (isBoardFull(game)) {
        SDL_RenderCopy(renderer, graphic.tied, NULL, NULL);
        graphic.presentScene();
        Mix_PlayChannel( -1, graphic.gEnd, 0 );
        waitUntilKeyPressed();
        game.init();
        graphic.render(game);
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
                 checkGameState(game, graphics.renderer, graphics);
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
