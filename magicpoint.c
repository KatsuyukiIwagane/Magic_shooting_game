#include "system.h"

void consumeMagicpoint() {
    if (player.magic >= 0)
        player.magic -= 1;
    else {
        printf("MPが足りません！");
        player.move.shoot = false;
    }
}