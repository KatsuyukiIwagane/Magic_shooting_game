#include "system.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Game game_info;

bool boss_appear = true; // ボスが出現するかどうかのフラグ, 動作確認のためにtrueに設定
float background_scroll_y = 0;
const int background_scroll_speed = 120;

TTF_Font* main_font = NULL;


void InitFonts() {
    main_font = TTF_OpenFont("./font/arial.ttf", 24);
    if (!main_font) {
        PrintError("フォントの読み込みに失敗しました");
    }
}

int InitWindow(const char *bg_file){
    /* SDL_image初期化 */
    if (IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG)) {
        return PrintError("failed to initialize SDL_image");
    }

    /** メインのウインドウ(表示画面)とレンダラーの作成 **/
    game_info.window = SDL_CreateWindow("禁忌地方", 80, 50, WD_Width, WD_Height, 0);
    if (game_info.window == NULL)
        return PrintError(SDL_GetError());

    game_info.render = SDL_CreateRenderer(game_info.window, -1, 0);
    if (game_info.render == NULL)
        return PrintError(SDL_GetError());

    /** 背景画像の読み込み **/
    game_info.background = IMG_LoadTexture(game_info.render, bg_file);
    if (game_info.background == NULL) {
        SDL_DestroyRenderer(game_info.render);
        SDL_DestroyWindow(game_info.window);
        return PrintError(SDL_GetError());
    }
    return 0;
}

void RenderFrame(double deltaTime) {
    /* 描画のクリア */
    SDL_RenderClear(game_info.render);

    /* 背景画像の描画 */
    DrawBackground(deltaTime);

    /* 敵の描画 */
    DrawEnemies();

    /* プレイヤーの描画 */
    DrawPlayer();

    /* 弾の描画 */
    DrawBullets();

    /* UIの描画 */
    DrawUI();

    /* サブUIの描画 */
    DrawSubUI();

    /* ボスの描画 */
    if (boss_appear)
        DrawBoss();
    else
        DrawGameClear();

    if (player.mp_short)
        DrawMPErrorMessage();

    if (player.health <= 0)
        DrawGameOver();
    
    DrawSpellList(game_info.render);
    /* 描画の更新 */
    SDL_RenderPresent(game_info.render);
}

void DrawBackground(double deltaTime) {
    int bg_h = WD_Height;

    // 背景1枚目
    SDL_Rect dest1 = {0, background_scroll_y, WD_Width, bg_h};
    SDL_RenderCopy(game_info.render, game_info.background, NULL, &dest1);

    // 背景2枚目（下にループして続く部分）
    SDL_Rect dest2 = {0, background_scroll_y + bg_h, WD_Width, bg_h};
    SDL_RenderCopy(game_info.render, game_info.background, NULL, &dest2);

    // スクロール値を減少（＝背景が上へ移動）
    background_scroll_y -= background_scroll_speed * deltaTime;

    // スクロールが1画面分進んだらリセット
    if (background_scroll_y <= -bg_h) {
        background_scroll_y = 0;
    }
}

void DrawEnemies() {
    for (int i = 0; i < MAX_ENEMY; i++) { //TODO: 烏しかでないよ～
        SDL_Rect dst = {
            enemiy_crows[i].x,
            enemiy_crows[i].y,
            enemiy_crows[i].width,
            enemiy_crows[i].height
        };
        SDL_RenderCopy(game_info.render, enemiy_crows[i].texture, NULL, &dst);
    }
}

void DrawPlayer() {
    if (player.texture != NULL) {
        SDL_Rect dest = {player.x, player.y, player.width, player.height};
        SDL_RenderCopy(game_info.render, player.texture, NULL, &dest);
    } else {
        PrintError("Player texture is not loaded");
    }
}

void DrawBullets() {
    // 弾を描画
    if (bullet_count > 0) {
        for (int i = 0; i < bullet_count; i++) {
            if (bullets[i].texture != NULL) {
                SDL_Rect dest = {bullets[i].x, bullets[i].y, bullets[i].width, bullets[i].height};
                SDL_RenderCopy(game_info.render, bullets[i].texture, NULL, &dest);
            } else {
                PrintError("Bullet texture is not loaded");
            }
        }
    }
    // 敵の弾を描画
    for (int i = 0; i < enemy_bullet_count; i++) {
        if (enemy_bullets[i].texture != NULL) {
            SDL_Rect dest = {enemy_bullets[i].x, enemy_bullets[i].y, enemy_bullets[i].width, enemy_bullets[i].height};
            SDL_RenderCopy(game_info.render, enemy_bullets[i].texture, NULL, &dest);
        } else {
            PrintError("Enemy bullet texture is not loaded");
        }
    }
}

void DrawUI() {
    // UIの描画処理を実装
}

void DrawBoss() {
    if (black.texture != NULL) {
        SDL_Rect dest = {black.x, black.y, black.width, black.height};
        SDL_RenderCopy(game_info.render, black.texture, NULL, &dest);
    } else {
        PrintError("Boss texture is not loaded");
    }
}


void DrawSpellList(SDL_Renderer* renderer) {

    int start_x = WD_Width - 180;
    int start_y = 20;
    int line_height = 32;

    for (int i = 0; i < SPELL_COUNT; i++) {
        SDL_Color color = spell_list[i].activated
                          ? (SDL_Color){255, 255, 255, 255} // 白
                          : (SDL_Color){150, 150, 150, 255}; // 灰色

        SDL_Surface* surface = TTF_RenderText_Blended(main_font, spell_list[i].name, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect dst = {start_x, start_y + i * line_height, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &dst);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void DrawGameClear() {
    static TTF_Font* font = NULL;
    if (!font) {
        font = TTF_OpenFont("./font/arial.ttf", 32); // 大きめのフォントサイズ
        if (!font) {
            PrintError("フォントの読み込みに失敗しました");
            return;
        }
    }

    const char* msg = "Game Clear!";
    SDL_Color color = {255, 255, 0, 255};  // 黄色

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, msg, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game_info.render, surface);
    

    // 中央に配置
    int text_width = surface->w;
    int text_height = surface->h;

    // 背景用の黒い矩形
    SDL_Rect bg_rect = {
        .x = (PLAY_WD_Width - text_width) / 2 - 10,
        .y = (PLAY_WD_Height - text_height) / 2 - 10,
        .w = text_width + 20,
        .h = text_height + 20
    };

    SDL_SetRenderDrawColor(game_info.render, 0, 0, 0, 200); // 半透明の黒
    SDL_RenderFillRect(game_info.render, &bg_rect);

    SDL_Rect dest = {
        .x = (PLAY_WD_Width - text_width) / 2,
        .y = (PLAY_WD_Height - text_height) / 2,
        .w = text_width,
        .h = text_height
    };

    SDL_RenderCopy(game_info.render, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}