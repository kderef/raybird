#pragma once

#include "rl.h"
#include <stdbool.h>

bool ui_button(rect bounds, const char* text, int font_size) {
    static const Color BG_COLOR = {0, 0, 0, 125};
    static const Color BG_COLOR_HOVER = {0, 0, 0, 80};
    static const Color BG_COLOR_CLICK = {0, 0, 0, 40};

    static vec2 mouse_pos;
    static int text_x, text_y, text_w;
    static bool mouse_hovered, button_clicked;
    static Color color;

    mouse_pos = GetMousePosition();
    mouse_hovered = CheckCollisionPointRec(mouse_pos, bounds);
    button_clicked = mouse_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    color = button_clicked?
        BG_COLOR_CLICK : mouse_hovered?
        BG_COLOR_HOVER : BG_COLOR;
    DrawRectangleRec(bounds, color);

    text_w = MeasureText(text, font_size);
    text_x = bounds.x + bounds.width / 2 - text_w / 2;
    text_y = bounds.y + bounds.height / 2 - font_size / 2;

    DrawText(text, text_x, text_y, font_size, WHITE);

    return button_clicked;
}

void draw_highscore(game_t* g, int y, Color color) {
    const char* highscore = TextFormat("Highscore: %lu", g->highscore);
    int highscore_size = MeasureText(highscore, 30);
    DrawText(highscore, WINDOW_WIDTH / 2 - highscore_size / 2, y, 30, color);
}