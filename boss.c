#include "system.h"

float boss_shoot_timer = 0;
const int BOSS_SHOOT_INTERVAL = 5;

Boss black = {
    .x = PLAY_WD_Width / 2 - 50, // 初期位置は画面中央
    .y = 100, // 画面上部から100px下
    .width = 100, // ボスの幅
    .height = 100, // ボスの高さ
    .health = 350, // 初期ライフ
    .magic = 200, // 初期魔力
    .speed = 1, // ボスの移動速度
    .texture = NULL, // ボスの画像は後で読み込む
    .move = {false, false, false, false, false} // 移動状態を初期化
};

void InitBoss() {
    // ボスの画像を読み込む
    black.texture = IMG_LoadTexture(game_info.render, "./image/enemy_black.png");
    if (black.texture == NULL) {
        PrintError(SDL_GetError());
    }

    // ボスの初期位置とサイズを設定
    black.x = PLAY_WD_Width / 2 - black.width / 2; // 中央に配置
    black.y = 100; // 画面上部から100px下
}

void BossAction(double deltaTime) {
    boss_shoot_timer += deltaTime;

    if (boss_shoot_timer >= BOSS_SHOOT_INTERVAL) {
        boss_shoot_timer = 0;

        const int num_bullets = 36;
        const float angle_step = 2 * MY_PI / num_bullets;

        for (int i = 0; i < num_bullets && enemy_bullet_count < MAX_BULLETS; i++) {
            float angle = i * angle_step;

            Bullet* b = &enemy_bullets[enemy_bullet_count++];
            b->x = black.x + black.width / 2 - 5;
            b->y = black.y + black.height / 2 - 5;
            b->width = 10;
            b->height = 10;
            b->speed = 180;
            b->angle = angle;
            b->texture = enemy_bullets[0].texture;  // テクスチャ共有でOK
        }
    }
}