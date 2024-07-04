#include "raylib.h"
#include "game/game.c"
#include "game/update.c"
#include "game/draw.c"

int main(void) {
    game_t game = game_new();

    unsigned flags = 0;
    game_init(&game, flags, WINDOW_WIDTH, WINDOW_HEIGHT, "RayBird");

    while (!game.should_close) {
        game_update(&game);
        game_draw(&game);
    }

    game_close(&game);

    return 0;
}