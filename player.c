#include "player.h"

void initPlayer(Player *player, SDL_Surface *window){
    player->x = 300;
    player->y = 400;
    player->w = 32;
    player->h = 32;
    player->color = SDL_MapRGB(window->format, 255, 255, 255);
}

void updatePlayer(Player *player, Uint8 *keystate) {
    if (keystate[SDLK_a]){
        player->x -= 5;
    }
    if (keystate[SDLK_d]){
        player->x += 5;
    }
    if (keystate[SDLK_w]){
        player->y -= 5;
    }
    if (keystate[SDLK_s]){
        player->y += 5;
    }
}

void drawPlayer(SDL_Surface *window, Player *player) {
    SDL_Rect rect = { player->x, player->y, player->w, player->h };
    SDL_FillRect(window, &rect, player->color);
}