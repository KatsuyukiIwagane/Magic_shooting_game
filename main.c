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
    if(InitWindow("image/background.jpg") < 0) {
        return PrintError("failed to initialize window");
    }

    /* プレイヤーの初期化 */
    InitPlayer();
    /* ボスの初期化 */
    InitBoss();

    /* ゲームループ */
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                HandleInput(&event); // 入力処理
            }
        }


        /*オブジェクトの更新 */
        UpdateOblects();
        /* 描画処理 */
        RenderFrame();
    }

    SDL_Quit();
    return 0;
}