#pragma once

#include "bird.c"
#include <stdbool.h>
#include "../rl.h"
#include <time.h>

typedef enum {
    GS_MENU = 0,
    GS_PLAYING,
    GS_PAUSED,
    GS_GAMEOVER,
} gamestate_t;

typedef struct {
    bool should_close;
    gamestate_t state;
    Texture bg;
    Texture pipe;
    float speed;
    unsigned long points;
    unsigned long highscore;
    bird_t bird;
} game_t;

#include "assets.c"

// Methods //

game_t game_new() {
    game_t g = {0};
    g.speed = 100;
    g.bird = bird_new();
    return g;
}

void game_close(game_t* g) {
    game_unload_assets(g);

    CloseWindow();
}

void game_init(game_t* g, unsigned int flags, int window_w, int window_h, const char* title) {
    SetConfigFlags(flags);
    InitWindow(window_w, window_h, title);

    SetExitKey(0);

#if !DEBUG
    SetTargetFPS(240);
#endif

    SetRandomSeed(time(NULL));

    game_load_assets(g);
}