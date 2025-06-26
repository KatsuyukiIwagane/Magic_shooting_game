#include <stdio.h>
#include <stdlib.h>
#include "player.h"


int main(int argc, char *argv[]){
    SDL_Surface *window;
    SDL_Event event;
    int running = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL初期化失敗\n");
        exit(-1);
    }

    if ((window = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE)) == NULL){
        printf("VideoMode初期化失敗\n");
        exit(-1);
    }
    Player player;
    initPlayer(&player, window);

    while (running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
            }
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = 0;
                    break;
                }
            }
        }
        Uint8 *keystate = SDL_GetKeyState(NULL);
        updatePlayer(&player, keystate);
        
        SDL_WM_SetCaption("SDL Game", "Software Exp");
        // SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
        SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
        drawPlayer(window, &player);
        SDL_Flip(window);
        SDL_Delay(16);
    }



    SDL_Quit();
    return 0;
}