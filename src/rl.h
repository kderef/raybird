#pragma once

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 800

#define SKY_COLOR (Color){0,153,204,255}

#include "raylib.h"
#include "raymath.h"

typedef Vector2 vec2;
typedef Rectangle rect;

typedef struct {int x; int y;} vec2i;

static const vec2 VEC2ZERO = {0};