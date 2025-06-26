#include <stdio.h>
#include <stdlib.h>
#include "system.h"


int main(int argc, char *argv[]){
    /** 初期化処理 **/
    /* SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        return PrintError(SDL_GetError());
    }

    /* ウィンドウの作成 */
    if(InitWindow("background.jpg") < 0) {
        return PrintError("failed to initialize window");
    }

    SDL_Quit();
    return 0;
}