#include "system.h"
#include <SDL2/SDL_ttf.h>



void DrawSubUI() {
    // UIの描画処理をここに実装
    // 右側に黒いエリアをつくり、プレイヤーのライフや魔力を表示する

    TTF_Font* font = TTF_OpenFont("./font/arial.ttf", 24);
    SDL_SetRenderDrawColor(game_info.render, 0, 0, 0, 128); // 半透明の黒色
    SDL_Rect ui_rect = {WD_Width - 200, 0, 200, WD_Height};
    SDL_RenderFillRect(game_info.render, &ui_rect);

    // プレイヤーのライフを表示
    // 残機の画像×ライフ数のように表示する
    char health_text[50];
    sprintf(health_text, "health: %d", player.health);
    SDL_Color color = {255, 255, 255, 255}; // 白色
    SDL_Surface* surface = TTF_RenderText_Solid(font, health_text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game_info.render, surface);
    

    SDL_Rect rect = {WD_Width - 200, 300 , surface->w, surface->h};
    SDL_RenderCopy(game_info.render, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}