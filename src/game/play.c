#pragma once

#include "game.c"
#include "../ui.c"

void draw_background(game_t* g, float offset) {
    DrawTextureRec(
        g->bg,
        (rect){
            offset, 0,
            WINDOW_WIDTH, g->bg.height
        },
        (vec2){0, WINDOW_HEIGHT - g->bg.height}, WHITE
    );
}

void draw_gameover(game_t* g) {
    static const Color color = {0, 0, 0, 100};
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);
    DrawText("GAME OVER!", 192, 50, 50, WHITE);

    draw_highscore(g, 100, WHITE);

    if (ui_button((rect){
        192, 200, 315, 70
    }, "RETURN TO MENU", 20)) {
        g->state = GS_MENU;
    }
}

void draw_game(game_t* g) {
    static float offset = 0;
    const float dt = GetFrameTime();
    static pipepair_t pipes = {
        .x = -200,
        .passed = true,
    };

    if (g->state == GS_PLAYING) {
        if (pipes.x <= -PIPE_WIDTH)
            pipes = random_pipes();
        else pipes.x -= dt * g->speed;

        bird_update(&g->bird);

        if (bird_hits_pipes(&g->bird, &pipes)) {
            g->state = GS_GAMEOVER;
            if (g->points > g->highscore) g->highscore = g->points;
            g->points = 0;
            pipes = random_pipes();
        } else if (!pipes.passed) {
            if (g->bird.pos.x > pipes.x + PIPE_WIDTH) {
                pipes.passed = true;
                g->points++;
                g->speed += log(g->points) * 10;
                //TraceLog(LOG_ERROR, "%f", g->speed);
            }
        }

        offset += dt * g->speed;
        if (offset >= g->bg.width)
            offset = 0;
    }

    ClearBackground(SKY_COLOR);
    draw_background(g, offset);

    // Calculate rotation based on velocity
    float rotation = Clamp(g->bird.velocity * 2.0f, -20.0f, 20.0f);

    DrawTexturePro(
        g->bird.sprite, (rect){0, 0, g->bird.sprite.width, g->bird.sprite.height},
        (rect){g->bird.pos.x, g->bird.pos.y, BIRD_WIDTH, BIRD_HEIGHT},
        (vec2){BIRD_WIDTH / 2.0f, BIRD_HEIGHT / 2.0f},
        rotation,
        WHITE
    );

    // TOP 
    DrawTexturePro(
        g->pipe,
        (rect){0, 0, g->pipe.width, -g->pipe.height},
        (rect){
            pipes.x,
            pipes.top_height - PIPE_HEIGHT,
            PIPE_WIDTH,
            PIPE_HEIGHT
        },
        VEC2ZERO, 0.0, WHITE
    );
    // BOTTOM
    DrawTexturePro(
        g->pipe,
        (rect){0, 0, g->pipe.width, g->pipe.height},
        (rect){
            pipes.x,
            pipes.top_height + pipes.gap,
            PIPE_WIDTH, 
            PIPE_HEIGHT
        },
        VEC2ZERO, 0.0, WHITE
    );

    const char* score = TextFormat("SCORE: %lu", g->points);
    int score_size = MeasureText(score, 80);
    DrawText(score, WINDOW_WIDTH / 2 - score_size / 2, 50, 80, WHITE);

    if (g->state == GS_GAMEOVER) draw_gameover(g);
}
