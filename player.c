#include "system.h"

Player player = {
    .x = PLAY_WD_Width / 2, // プレイヤーの初期位置は画面中央
    .y = PLAY_WD_Height - 100, // 画面下部から100px上
    .width = PLAYER_WIDTH , // プレイヤーの幅
    .height = PLAYER_HEIGHT, // プレイヤーの高さ
    .health = PLAYER_HEALTH, // 初期ライフ
    .magic = PLAYER_MAGIC, // 初期魔力
    .speed = PLAYER_BASE_SPEED, // プレイヤーの移動速度
    .texture = NULL // プレイヤーの画像は後で読み込む
};


void InitPlayer() {
    // プレイヤーの画像を読み込む
    player.texture = IMG_LoadTexture(game_info.render, "./image/player.png");
    if (player.texture == NULL) {
        PrintError(SDL_GetError());
    }

    // プレイヤーの初期位置とサイズを設定
    player.x = PLAY_WD_Width / 2 - player.width / 2; // 中央に配置
    player.y = PLAY_WD_Height - 10; // 画面下部から10px上
}