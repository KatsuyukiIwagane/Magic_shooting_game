#include "system.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Game game_info;

bool boss_appear = true; // ボスが出現するかどうかのフラグ, 動作確認のためにtrueに設定

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

void RenderFrame() {
    /* 描画のクリア */
    SDL_RenderClear(game_info.render);

    /* 背景画像の描画 */
    DrawBackground();

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

    if (player.mp_short)
        DrawMPErrorMessage();

    if (player.health <= 0)
        DrawGameOver();
    
    DrawSpellList(game_info.render);
    /* 描画の更新 */
    SDL_RenderPresent(game_info.render);
}

void DrawBackground() {
    SDL_Rect dest = {0, 0, WD_Width, WD_Height};
    SDL_RenderCopy(game_info.render, game_info.background, NULL, &dest);
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

    TTF_Font* font = TTF_OpenFont("./font/arial.ttf", 24);
    int start_x = WD_Width - 180;
    int start_y = 20;
    int line_height = 32;

    for (int i = 0; i < SPELL_COUNT; i++) {
        SDL_Color color = spell_list[i].activated
                          ? (SDL_Color){255, 255, 255, 255} // 白
                          : (SDL_Color){150, 150, 150, 255}; // 灰色

        SDL_Surface* surface = TTF_RenderText_Blended(font, spell_list[i].name, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect dst = {start_x, start_y + i * line_height, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &dst);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}