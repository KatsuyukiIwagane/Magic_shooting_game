#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    int x, y, w, h;
    Uint32 color;
} Player;

void initPlayer(Player *player, SDL_Surface *window);
void updatePlayer(Player *player, Uint8 *keystate);
void drawPlayer(SDL_Surface *window, Player *player);

#endif