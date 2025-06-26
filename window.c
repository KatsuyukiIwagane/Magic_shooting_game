#include "system.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

Game game_info;


int InitWindow(const char *bg_file){
    /* SDL_image初期化 */
    if (IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG)) {
        return PrintError("failed to initialize SDL_image");
    }

    /** メインのウインドウ(表示画面)とレンダラーの作成 **/
    game_info.window = SDL_CreateWindow("禁忌地方", 80, 50, WD_Width, WD_Height, 0);
    if (game_info.window == NULL)
        return PrintError(SDL_GetError());

    game_info.render = SDL_CreateRenderer(game_info.window, -1, 0);
    if (game_info.render == NULL)
        return PrintError(SDL_GetError());

    /** 背景画像の読み込み **/
    game_info.background = IMG_LoadTexture(game_info.render, bg_file);
    if (game_info.background == NULL) {
        SDL_DestroyRenderer(game_info.render);
        SDL_DestroyWindow(game_info.window);
        return PrintError(SDL_GetError());
    }
}