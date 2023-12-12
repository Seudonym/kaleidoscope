#pragma once
#include "Fractal.hpp"

class Mandelbrot : public Fractal {
public:
    void render() const override;
};