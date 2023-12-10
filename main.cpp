#include <stdio.h>
#include <mpfr.h>
#include <iostream>

int main(int, char**){
    mpfr_t x;
    mpfr_init2(x, 256);
    mpfr_set_d(x, 1.0, MPFR_RNDN);
    mpfr_exp(x, x, MPFR_RNDN);
    mpfr_printf("%.128Rf\n", x);
    mpfr_clear(x);
    return 0;
}
