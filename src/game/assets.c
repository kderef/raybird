#pragma once

#include "game.c"

#define INCBIN_PREFIX bin_
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include "incbin.h"

INCBIN(bg, "assets/bg.png");
INCBIN(bird, "assets/bird.png");
INCBIN(pipe, "assets/pipe.png");

Texture load_texture_from_mem(const char* filetype, const unsigned char* data, int data_size) {
    Image img = LoadImageFromMemory(filetype, data, data_size);
    Texture txt = LoadTextureFromImage(img);
    SetTextureFilter(txt, TEXTURE_FILTER_POINT);
    UnloadImage(img);
    return txt;
}

void game_load_assets(game_t* g) {
    g->bg = load_texture_from_mem(".png", bin_bg_data, bin_bg_size);
    g->bird.sprite = load_texture_from_mem(".png", bin_bird_data, bin_bird_size);
    g->pipe = load_texture_from_mem(".png", bin_pipe_data, bin_pipe_size);
}

void game_unload_assets(game_t* g) {
    UnloadTexture(g->bg);
    UnloadTexture(g->bird.sprite);
    UnloadTexture(g->pipe);
}