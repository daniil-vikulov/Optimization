#ifndef TAYLOREXP_H
#define TAYLOREXP_H

#include "consts/GccConsts.h"
#include "consts/Consts.h"

namespace adaai::solution {

    ///@brief calculates exponent using Taylor formula
    template<typename F>
    F expTaylor(F x, int N) {
        F sum = 1.0;
        F term = 1.0;
        F curr_eps = x;
        int n = 1;

        if (x > 0) {
            curr_eps *= Sqrt2<F>;
        }

        for (int i = 1; i < N + 1; i++) {
            term *= x / n;
            sum += term;
            curr_eps *= x / (n + 1);
            n++;
        }

        return sum;
    }
}

#endif