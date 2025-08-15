#ifndef PADEEXP_H
#define PADEEXP_H

#include <vector>

#include "consts/GccConsts.h"
#include "consts/Consts.h"

namespace adaai::solution {
    ///@brief calculates exponent using Pade approach
    template<typename F>
    F expPade(F x) {
        std::vector<F> coefficients = {1.0, 56.0, 1512.0, 25200.0, 277200.0, 1995840.0, 8648640.0, 17297280.0};
        F curr_x = 1.0;
        F numerator = 0.0;
        F denominator = 0.0;
        for (int i = coefficients.size() - 1; i >= 0; i--) {
            F curr_term = coefficients[i] * curr_x;
            if (i % 2 != 0) {
                denominator += curr_term;
            } else {
                denominator -= curr_term;
            }
            numerator += curr_term;
            curr_x *= x;
        }
        F res = numerator / denominator;
        return res;
    }
}

#endif