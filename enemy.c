#include "system.h"
#include <time.h>

Enemy enemiy_crows[MAX_ENEMY]; // 敵(暫定烏)の配列

SDL_Texture* enemy_textures[ENEMY_TYPE_COUNT];

void InitEnemyTextures() {
    enemy_textures[ENEMY_CROW] = IMG_LoadTexture(game_info.render, "./image/enemy_crow.png");
    if (!enemy_textures[ENEMY_CROW]) {
        PrintError("敵テクスチャの読み込みに失敗しました");
    }
}

void InitEnemies() {
    //敵の初期化処理
    InitEnemyTextures(); // 敵のテクスチャを初期化
    srand((unsigned int)time(NULL));
    for (int j = 0; j < ENEMY_TYPE_COUNT; j++) {
        // 敵の初期化処理
        for (int i = 0; i < MAX_ENEMY; i++) {
            enemiy_crows[i].x = -999;//rand() % (PLAY_WD_Width - ENEMY_WIDTH); // 敵を上半分にランダムに配置 //TODOランダムな配置ではなく決まった列の配置をする関数を作る
            enemiy_crows[i].y = -999;//rand() % (PLAY_WD_Height / 2);
            enemiy_crows[i].health = 0; //敵のライフ
            enemiy_crows[i].width = ENEMY_WIDTH; // 敵の幅
            enemiy_crows[i].height = ENEMY_WIDTH; // 敵の高さ
            enemiy_crows[i].speed = ENEMY_BASE_SPEED; // 敵の移動速度
            enemiy_crows[i].direction = 1;
            enemiy_crows[i].texture = enemy_textures[j]; // 敵の画像
            if (enemiy_crows[i].texture == NULL) {
                PrintError(SDL_GetError());
            }
            enemiy_crows[i].move = (Move){false, false, false, false, false}; // 移動状態を初期化
        }
    }
}



void drawEnemies() {
    // 敵の描画処理をここに実装
    // 例: 敵の画像をレンダラーに描画する
    // 現在は何も実装していないが、必要に応じて追加すること
}