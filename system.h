#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define WD_Width 720 // ウィンドウの幅
#define WD_Height 960 // ウィンドウの高さ

//ゲームの情報
typedef struct {
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Texture* background; // 背景画像
} Game;

//敵の情報
typedef struct {
    int x, y, w, h;
    Uint32 color;
} Enemy;

//プレイヤーの情報
typedef struct {
    int x, y, w, h;
    Uint32 color;
} Player;

extern Game game_info;

extern int InitWindow(const char *bg_file);
extern int PrintError(const char* str);
extern void HandleInput(SDL_Event* event);
extern void UpdateOblects();
extern void RenderFrame(); // 全画面の描画
extern void DrawBackground(); // 背景画像の描画
extern void DrawEnemies(); // 敵の描画
extern void DrawPlayer(); // プレイヤーの描画
extern void DrawBullets(); // 弾の描画
extern void DrawUI(); // UIの描画
extern void UpdatePlayer(); // プレイヤーの更新
extern void UpdateEnemies(); // 敵の更新
extern void UpdateBullets(); // 弾の更新
extern void UpdateUI(); // UIの更新

#endif