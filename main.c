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
    if(InitWindow("image/background.png") < 0) {
        return PrintError("failed to initialize window");
    }

    /* TTFの初期化 */
    if (TTF_Init() == -1) {
        SDL_DestroyRenderer(game_info.render);
        SDL_DestroyWindow(game_info.window);
        return PrintError(TTF_GetError());
    }

    MenuSelection selected = ShowStartMenu();
    if (selected != MENU_START) {
        SDL_Quit();
        return 0;
    }

    /* プレイヤーの初期化 */
    InitPlayer();
    /* プレイヤーの初期化 */
    InitEnemies();
    /* ボスの初期化 */
    InitBoss();
    /* 弾の初期化 */
    InitBullets();
    /* UI画像の初期化 */
    InitUI();

    /* ゲームループ */
    SDL_Event event;
    bool running = true;
    LoadStageScript("stage1.csv");
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                HandleInput(&event); // 入力処理
                HandleSpellInput(&event); // スペル入力処理
            }
        }

        /*ステージの更新*/
        UpdateStage();
        /*オブジェクトの更新 */
        UpdateOblects();
        /* 描画処理 */
        RenderFrame();
    }

    SDL_Quit();
    return 0;
}