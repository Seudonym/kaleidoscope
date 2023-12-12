#pragma once
#include <stdio.h>
#include <mpfr.h>
namespace Globals {
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float ZOOM;
extern float X, Y;
extern int ITERATIONS;

extern mpfr_t x, y, zoom;
extern mpfr_t stride;
} // namespace Globals