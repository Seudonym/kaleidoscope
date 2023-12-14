#pragma once

#include <mpfr.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <thread>

#include "Globals.hpp"

class Fractal {
protected:
    uint8_t *pixels;
public:
    Fractal() {
        pixels = new uint8_t[4 * Globals::SCREEN_WIDTH * Globals::SCREEN_HEIGHT];
    }
    virtual void render() const = 0;
    uint8_t* getPixels() const {
        return pixels;
    }
};