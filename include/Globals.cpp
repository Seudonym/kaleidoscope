#include "Globals.hpp"

int Globals::SCREEN_WIDTH = 640;
int Globals::SCREEN_HEIGHT = 640;
int Globals::ITERATIONS = 100;

mpfr_t Globals::x, Globals::y, Globals::zoom;
mpfr_t Globals::stride;

int Globals::NUM_THREADS;