#include "system.h"

void consumeMagicpoint(BulletType type) {
    int cost;
    switch (type) {
        case BULLET_NOMAL:
            cost = 1;
            break;
        case BULLET_WAVE:
            cost = 4;
            break;
        default:
            cost = 1;
    }
    if (player.magic > 0)
        player.magic -= cost;
    else {
        player.magic = 0;
        player.mp_short = true;
        player.move.shoot = false;
    }
}