#include "system.h"
#include <stdbool.h>

void HandleInput(SDL_Event* event) {
    if (event->key.repeat != 0)
        return; // キーリピートイベントは無視
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
                    break;
                case SDLK_c:
                    switch (player.bullet_type) {
                    case BULLET_NOMAL:
                        player.bullet_type = BULLET_WAVE;
                        break;
                    case BULLET_WAVE:
                        player.bullet_type = BULLET_NOMAL;
                        break;
                    default:
                        break;
                    }
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

MenuSelection ShowStartMenu() {
    TTF_Font* font = TTF_OpenFont("./font/arial.ttf", 36);
    if (!font) {
        PrintError("Font load failed");
        return MENU_QUIT;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Event event;
    MenuSelection selection = MENU_NONE;

    while (selection == MENU_NONE) {
        SDL_SetRenderDrawColor(game_info.render, 0, 0, 0, 255);
        SDL_RenderClear(game_info.render);

        const char* title = "=== Select Menu ===";
        const char* start = "Press S: START";
        const char* quit = "Press Q: QUIT";

        const char* lines[] = {title, start, quit};
        for (int i = 0; i < 3; i++) {
            SDL_Surface* surface = TTF_RenderUTF8_Blended(font, lines[i], white);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(game_info.render, surface);
            SDL_Rect dest = {
                (WD_Width - surface->w) / 2,
                150 + i * 60,
                surface->w,
                surface->h
            };
            SDL_RenderCopy(game_info.render, texture, NULL, &dest);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(game_info.render);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                selection = MENU_QUIT;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_s: selection = MENU_START; break;
                    case SDLK_q: selection = MENU_QUIT; break;
                }
            }
        }

        SDL_Delay(16);  // 軽負荷でループ
    }

    TTF_CloseFont(font);
    return selection;
}