#include "system.h"

Player player = {
    .x = WD_Width / 2, // 初期位置は画面中央
    .y = WD_Height - 100, // 画面下部から100px上
    .width = 50, // プレイヤーの幅
    .height = 50, // プレイヤーの高さ
    .health = 100, // 初期ライフ
    .magic = 50, // 初期魔力
    .texture = NULL // プレイヤーの画像は後で読み込む
};


void InitPlayer() {
    // プレイヤーの画像を読み込む
    player.texture = IMG_LoadTexture(game_info.render, "./image/player.png");
    if (player.texture == NULL) {
        PrintError(SDL_GetError());
    }

    // プレイヤーの初期位置とサイズを設定
    player.x = WD_Width / 2 - player.width / 2; // 中央に配置
    player.y = WD_Height - player.height - 10; // 画面下部から10px上
}