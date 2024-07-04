#pragma once

#include "../rl.h"
#include <stdint.h>

#define BIRD_WIDTH 68
#define BIRD_HEIGHT 64

#define FALL_SPEED 50.0f

typedef struct {
    vec2 pos;
    float velocity;
    Texture sprite;
} bird_t;

#define PIPE_WIDTH 120
#define PIPE_HEIGHT 800

typedef struct {
    float x;
    int top_height;
    int gap;
    bool passed;
} pipepair_t;

pipepair_t random_pipes() {
    pipepair_t pipes = {0};
    pipes.x = WINDOW_WIDTH + PIPE_WIDTH;
    pipes.gap = GetRandomValue(120, 140);
    pipes.top_height = GetRandomValue(100, 400);
    return pipes;
}

bird_t bird_new() {
    return (bird_t) {
        .pos = (vec2){100, WINDOW_HEIGHT / 2 - BIRD_HEIGHT / 2},
        .velocity = 0.0f
    };
}

void bird_update(bird_t* b) {
    const float dt = GetFrameTime();

    #define GRAVITY 500.0f
    #define JUMP 200.0f

    if (IsKeyPressed(KEY_SPACE)) {
        b->velocity = -JUMP;
    }

    b->velocity += GRAVITY * dt;
    b->pos.y += b->velocity * dt;

    if (b->pos.y >= WINDOW_HEIGHT - BIRD_HEIGHT) {
        b->velocity = 0;
        b->pos.y = WINDOW_HEIGHT - BIRD_HEIGHT;
    } else if (b->pos.y <= 0) {
        b->velocity = 0;
        b->pos.y = 0;
    }
}

bool bird_hits_pipes(bird_t* bird, pipepair_t* pipes) {
    bool x_collides = bird->pos.x + BIRD_WIDTH >= pipes->x && bird->pos.x <= pipes->x + PIPE_WIDTH;
    bool y_collides_top = bird->pos.y <= pipes->top_height;
    bool y_collides_bot = bird->pos.y + BIRD_HEIGHT >= pipes->top_height + pipes->gap;
    return x_collides && (y_collides_top || y_collides_bot);
}
