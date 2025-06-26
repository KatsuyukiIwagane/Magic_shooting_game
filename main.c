#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "system.h"


int main(int argc, char *argv[]){
    /** 初期化処理 **/
    /* SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        return PrintError(SDL_GetError());
    }

    /* ウィンドウの作成 */
    if(InitWindow("background.jpg") < 0) {
        return PrintError("failed to initialize window");
    }

    /* ゲームループ */
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        /* レンダリング */
        SDL_RenderClear(game_info.render);
        SDL_RenderCopy(game_info.render, game_info.background, NULL, NULL);
        SDL_RenderPresent(game_info.render);
    }

    SDL_Quit();
    return 0;
}