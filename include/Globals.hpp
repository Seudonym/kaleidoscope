#pragma once
#include <stdio.h>
#include <mpfr.h>

#ifdef DEBUG
#define DEBUG_LOG(x) std::cerr << x << std::endl << std::flush;
#else
#define DEBUG_LOG(x)
#endif
namespace Globals {
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float ZOOM;
extern float X, Y;
extern int ITERATIONS;

extern mpfr_t x, y, zoom;
extern mpfr_t stride;

extern int NUM_THREADS;
} // namespace Globals