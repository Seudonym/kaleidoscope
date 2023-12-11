#pragma once

#include <mpfr.h>
#include <stdio.h>

#include "Globals.hpp"

class Mandelbrot {
public:
    Mandelbrot();

    virtual void render() const = 0;
};