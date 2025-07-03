#include "system.h"
#include <SDL2/SDL_ttf.h>

UI ui_info;

void InitUI() {
    ui_info.health_icon = IMG_LoadTexture(game_info.render, "./image/health.png");
    SDL_SetTextureBlendMode(ui_info.health_icon, SDL_BLENDMODE_BLEND);
    if (ui_info.health_icon == NULL) {
        PrintError(SDL_GetError());
    }
}

void DrawSubUI() {

    // フォント初期化
    static TTF_Font* font = NULL;
    if (!font) {
        font = TTF_OpenFont("./font/arial.ttf", 24);
        if (!font) {
            PrintError("フォント読み込み失敗");
            return;
        }
    }

    // UIの描画処理をここに実装
    // 右側に黒いエリアをつくり、プレイヤーのライフや魔力を表示する

    SDL_SetRenderDrawColor(game_info.render, 0, 0, 0, 128); // 半透明の黒色
    SDL_Rect ui_rect = {WD_Width - 200, 0, 200, WD_Height};
    SDL_RenderFillRect(game_info.render, &ui_rect);

    
    // MP数値表示
    char magic_text[50];
    sprintf(magic_text, "MP: %d", player.magic);
    SDL_Color mp_color = {0, 128, 255, 255}; // 青系の色
    SDL_Surface* mp_surface = TTF_RenderText_Blended(font, magic_text, mp_color);
    SDL_Texture* mp_texture = SDL_CreateTextureFromSurface(game_info.render, mp_surface);

    SDL_Rect mp_rect = {
        .x = WD_Width - 200 + 20,
        .y = 250, // ライフの上
        .w = mp_surface->w,
        .h = mp_surface->h
    };

    SDL_RenderCopy(game_info.render, mp_texture, NULL, &mp_rect);
    SDL_FreeSurface(mp_surface);
    SDL_DestroyTexture(mp_texture);

    // ライフアイコンのサイズ・間隔
    int icon_size = 48;
    int spacing = 10;
    int start_x = WD_Width - 200 + 20;
    int start_y = 300;

    // プレイヤーのライフ分アイコンを描画
    for (int i = 0; i < player.health; i++) {
        SDL_Rect dst = {
            start_x + i * (icon_size + spacing),
            start_y,
            icon_size,
            icon_size
        };
        SDL_RenderCopy(game_info.render, ui_info.health_icon, NULL, &dst);
    }
}


void DrawMPErrorMessage() {
    static TTF_Font* font = NULL;
    if (!font) {
        font = TTF_OpenFont("./font/arial.ttf", 32); // 大きめのフォントサイズ
        if (!font) {
            PrintError("フォントの読み込みに失敗しました");
            return;
        }
    }

    const char* msg = "Short Magic Points!";
    SDL_Color color = {255, 0, 0, 255};  // 赤色

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, msg, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game_info.render, surface);
    

    // 中央に配置
    int text_width = surface->w;
    int text_height = surface->h;

    // 背景用の黒い矩形
    SDL_Rect bg_rect = {
        .x = (PLAY_WD_Width - text_width) / 2 - 10,
        .y = (PLAY_WD_Height - text_height) / 2 - 10,
        .w = text_width + 20,
        .h = text_height + 20
    };

    SDL_SetRenderDrawColor(game_info.render, 0, 0, 0, 200); // 半透明の黒
    SDL_RenderFillRect(game_info.render, &bg_rect);

    SDL_Rect dest = {
        .x = (PLAY_WD_Width - text_width) / 2,
        .y = (PLAY_WD_Height - text_height) / 2,
        .w = text_width,
        .h = text_height
    };

    SDL_RenderCopy(game_info.render, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}