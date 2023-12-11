#include <stdio.h>
#include <mpfr.h>
#include <iostream>

#include <Globals.hpp>

int main(int, char**){
    mpfr_t re, im, re2, im2, cre, cim, T;

    mpfr_set_default_prec(32);
    mpfr_inits(re, im, re2, im2, cre, cim, T, (mpfr_ptr) 0);

    std::cout << "P3" << std::endl;
    std::cout << Globals::SCREEN_WIDTH << " " << Globals::SCREEN_HEIGHT << std::endl;
    std::cout << "255" << std::endl;
    for (int j = 0; j < Globals::SCREEN_HEIGHT; j++) {
        for (int i = 0; i < Globals::SCREEN_WIDTH; i++) {
            mpfr_set_flt(cre, (float) i / Globals::SCREEN_WIDTH * 4.0 - 2.0, MPFR_RNDN);
            mpfr_set_flt(cim, (float) j / Globals::SCREEN_HEIGHT * 4.0 - 2.0, MPFR_RNDN);

            mpfr_set_flt(re, 0.0, MPFR_RNDN);
            mpfr_set_flt(im, 0.0, MPFR_RNDN);
            mpfr_set_flt(re2, 0.0, MPFR_RNDN);
            mpfr_set_flt(im2, 0.0, MPFR_RNDN);

            int iter = 0;
            while (iter < 255) {
                mpfr_mul(re2, re, re, MPFR_RNDN);
                mpfr_mul(im2, im, im, MPFR_RNDN);

                mpfr_mul(im, im, re, MPFR_RNDN);
                mpfr_mul_2exp(im, im, 1, MPFR_RNDN);
                mpfr_add(im, im, cim, MPFR_RNDN);

                mpfr_sub(re, re2, im2, MPFR_RNDN);
                mpfr_add(re, re, cre, MPFR_RNDN);

                mpfr_add(T, re2, im2, MPFR_RNDN);

                if (mpfr_cmp_ui(T, 4) > 0) {
                    break;
                }
                iter++;
            } 

            std::cout << iter << " " << iter << " " << iter << std::endl;
        }
    }

    mpfr_clears(re, im, re2, im2, cre, cim, T, (mpfr_ptr) 0);
}
