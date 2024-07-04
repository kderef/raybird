#pragma once

#include "game.c"
#include "../ui.c"
#include "play.c"

void draw_menu(game_t*);
void draw_game(game_t*);

void game_draw(game_t* g) {
    BeginDrawing();

    switch (g->state) {
    case GS_MENU: draw_menu(g); break;
    case GS_PLAYING:
    case GS_GAMEOVER:
    case GS_PAUSED: draw_game(g); break;
    }

#if DEBUG
    DrawFPS(0, 0);
#endif
    EndDrawing();
}

void draw_menu(game_t* g) {
    // Variables //
    static vec2 screen_size, btn_size, screen_center;
    static rect btn_bounds;
    static const char* title = "RayBird";
    static const int font_size = 50, font_size_l = 100;

    // Initialize //
    screen_size = (vec2){GetScreenWidth(), GetScreenHeight()};
    screen_center = Vector2Divide(screen_size, (vec2){2, 2});
    btn_size = Vector2Divide(screen_size, (vec2){2, 8});

    btn_bounds = (rect) {
        screen_center.x - btn_size.x / 2,
        screen_center.y - btn_size.y,
        btn_size.x, btn_size.y
    };

    // Begin Drawing //
    ClearBackground(SKY_COLOR);
    DrawTexture(
        g->bg, 0, screen_size.y - g->bg.height,
        WHITE
    );

    // 155 = (window_width / 2) - (text_width / 2)
    DrawText(title, 155, 100, font_size_l, WHITE);
    draw_highscore(g, 200, LIGHTGRAY);

    rect button_bounds = {
        WINDOW_WIDTH / 2 - 400 / 2,
        300,
        400, 75,
    };

    // Draw buttons
    if (ui_button(button_bounds, "PLAY", 50)) {
        g->state = GS_PLAYING;
    }
    button_bounds.y += button_bounds.height * 1.5;
    if (ui_button(button_bounds, "EXIT", 50)) {
        g->should_close = true;
    }
}