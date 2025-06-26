#include "system.h"

void HandleInput(SDL_Event* event) {
    Player* player = (Player*)event->user.data1; // プレイヤー情報を取得

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_UP:
                    player->y -= 10; // 上に移動
                    break;
                case SDLK_DOWN:
                    player->y += 10; // 下に移動
                    break;
                case SDLK_LEFT:
                    player->x -= 10; // 左に移動
                    break;
                case SDLK_RIGHT:
                    player->x += 10; // 右に移動
                    break;
            }
            break;
        default:
            break;
    }
}