#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#define WD_Width 720 // ウィンドウの幅
#define WD_Height 960 // ウィンドウの高さ

//ゲームの情報
typedef struct {
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Texture* background; // 背景画像
} Game;

typedef struct {
    bool up; // 上に移動
    bool down; // 下に移動
    bool left; // 左に移動
    bool right; // 右に移動
    bool shoot; // 弾を撃つ
} Move;

//敵の情報
typedef struct {
    int x, y;
    Uint32 color;
} Enemy;

//プレイヤーの情報
typedef struct {
    int x, y;
    int width, height; // プレイヤーの幅と高さ
    int health; // プレイヤーのライフ
    int magic; // プレイヤーの魔力
    int speed; // プレイヤーの移動速度
    SDL_Texture* texture; // プレイヤーの画像
    Move move; // 移動状態
} Player;

extern Game game_info;
extern Player player;

extern int InitWindow(const char *bg_file);
extern void InitPlayer(); // プレイヤーの初期化
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