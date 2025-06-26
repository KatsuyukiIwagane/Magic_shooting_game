#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define WD_Width 720 // ウィンドウの幅
#define WD_Height 960 // ウィンドウの高さ

//ゲームの情報
typedef struct {
    SDL_Window *window;
    SDL_Renderer *render;
} Game;

typedef struct {
    int x, y, w, h;
    Uint32 color;
} Player;

extern Game game_info;


#endif