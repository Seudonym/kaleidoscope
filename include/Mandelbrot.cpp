#include <iostream>
#include "Mandelbrot.hpp"

void Mandelbrot::render() const {
    auto renderBatch = [this](int startX, int startY, int endX, int endY) {
        mpfr_t re, im, re2, im2, cre, cim, T;
        mpfr_set_default_prec(128);
        mpfr_inits(re, im, re2, im2, cre, cim, T, (mpfr_ptr)0);

        for (int j = startY; j < endY; j++) {
            mpfr_set_flt(cim, (float)j / Globals::SCREEN_HEIGHT * 2.0 - 1.0, MPFR_RNDN);
            mpfr_div(cim, cim, Globals::zoom, MPFR_RNDN);
            mpfr_add(cim, cim, Globals::y, MPFR_RNDN);
            for (int i = startX; i < endX; i++) {
                mpfr_set_flt(cre, (float)i / Globals::SCREEN_WIDTH * 2.0 - 1.0, MPFR_RNDN);
                mpfr_div(cre, cre, Globals::zoom, MPFR_RNDN);
                mpfr_add(cre, cre, Globals::x, MPFR_RNDN);

                mpfr_set_flt(re, 0.0, MPFR_RNDN);
                mpfr_set_flt(im, 0.0, MPFR_RNDN);
                mpfr_set_flt(re2, 0.0, MPFR_RNDN);
                mpfr_set_flt(im2, 0.0, MPFR_RNDN);

                int iter = 0;
                while (iter < Globals::ITERATIONS) {
                    mpfr_mul(re2, re, re, MPFR_RNDN);
                    mpfr_mul(im2, im, im, MPFR_RNDN);

                    mpfr_mul(im, im, re, MPFR_RNDN);
                    mpfr_mul_ui(im, im, 2, MPFR_RNDN);
                    mpfr_add(im, im, cim, MPFR_RNDN);

                    mpfr_sub(re, re2, im2, MPFR_RNDN);
                    mpfr_add(re, re, cre, MPFR_RNDN);

                    // mpfr_add(T, re2, im2, MPFR_RNDN);

                    // if (mpfr_cmp_ui(T, 4) > 0) {
                        // break;
                    // }
                    if (mpfr_cmpabs_ui(re, 2) > 0 || mpfr_cmpabs_ui(im, 2) > 0) {
                        break;
                    }
                    iter++;
                }

                int color = iter * 255 / Globals::ITERATIONS;

                int pixelIndex = 4 * (j * Globals::SCREEN_WIDTH + i);
                this->pixels[pixelIndex] = color;
                this->pixels[pixelIndex + 1] = color;
                this->pixels[pixelIndex + 2] = color;
                this->pixels[pixelIndex + 3] = 255;
            }
        }
        mpfr_clears(re, im, re2, im2, cre, cim, T, (mpfr_ptr)0);
    };

    std::vector<std::thread> threads;
    int startX = 0;
    int batchWidth = Globals::SCREEN_WIDTH / Globals::NUM_THREADS;
    for (int i = 0; i < Globals::NUM_THREADS; ++i) {
        int endX = (i == Globals::NUM_THREADS - 1) ? Globals::SCREEN_WIDTH : startX + batchWidth;
        threads.push_back(std::thread(renderBatch, startX, 0, endX, Globals::SCREEN_HEIGHT));
        startX = endX;
    }

    for (auto &thread : threads) {
        thread.join();
    }
}
