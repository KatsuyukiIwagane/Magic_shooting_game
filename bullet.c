#include "system.h"

Bullet nomal_bullets[MAX_BULLETS]; // 弾の配列
int bullet_count = 0; // 弾の数


void InitBullets() {
    // 弾の初期化処理
    SDL_Texture* bullet_texture = IMG_LoadTexture(game_info.render, "./image/nomal_bullet.png"); // 弾のテクスチャ
    for (int i = 0; i < MAX_BULLETS; i++) {
        nomal_bullets[i].x = 0;
        nomal_bullets[i].y = 0;
        nomal_bullets[i].width = 25; // 弾の幅
        nomal_bullets[i].height = 25; // 弾の高さ
        nomal_bullets[i].speed = 3; // 弾の移動速度
        nomal_bullets[i].texture = bullet_texture;
        if (nomal_bullets[i].texture == NULL) {
            PrintError(SDL_GetError());
        }
        nomal_bullets[i].move = (Move){false, false, false, false, false}; // 移動状態を初期化
    }

}

