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
    // UIの描画処理をここに実装
    // 右側に黒いエリアをつくり、プレイヤーのライフや魔力を表示する

    SDL_SetRenderDrawColor(game_info.render, 0, 0, 0, 128); // 半透明の黒色
    SDL_Rect ui_rect = {WD_Width - 200, 0, 200, WD_Height};
    SDL_RenderFillRect(game_info.render, &ui_rect);

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