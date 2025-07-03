#include "system.h"

Boss black = {
    .x = PLAY_WD_Width / 2 - 50, // 初期位置は画面中央
    .y = 100, // 画面上部から100px下
    .width = 100, // ボスの幅
    .height = 100, // ボスの高さ
    .health = 50, // 初期ライフ
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

void BossAction() {
    //ボスの行動
}