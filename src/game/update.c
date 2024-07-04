#pragma once

#include "../rl.h"
#include "game.c"

void game_update(game_t* g) {
    g->should_close |= WindowShouldClose();
}