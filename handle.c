#include "system.h"
#include <stdbool.h>

void HandleInput(SDL_Event* event) {

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_w:
                    player.move.up = true; // 上に移動
                    break;
                case SDLK_s:
                    player.move.down = true; // 下に移動
                    break;
                case SDLK_a:
                    player.move.left = true; // 左に移動
                    break;
                case SDLK_d:
                    player.move.right = true; // 右に移動
                    break;
                case SDLK_SPACE:
                    player.move.shoot = true; // 弾を撃つ
            }
            break;
        default:
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                case SDLK_w:
                    player.move.up = false; // 上に移動を停止
                    break;
                case SDLK_s:
                    player.move.down = false; // 下に移動を停止
                    break;
                case SDLK_a:
                    player.move.left = false; // 左に移動を停止
                    break;
                case SDLK_d:
                    player.move.right = false; // 右に移動を停止
                    break;
                case SDLK_SPACE:
                    player.move.shoot = false; // 弾を撃つのを停止
                    break;
                default:
                    break;
            }
        
    }
}