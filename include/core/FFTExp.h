#ifndef FFT_EXP_H
#define FFT_EXP_H

#include <vector>

#include "consts/Consts.h"
#include "consts/GccConsts.h"

namespace adaai::solution {
    ///@brief calculates T_0(x)...T_{n-1}(x) and saves into the array. T_i(x) - i-th coefficient in Chebyshev polynomial in a specific point x
    template<typename F>
    std::vector<F> getT(F x, int n) {
        std::vector<F> coefficients(n);
        coefficients[0] = 1;
        coefficients[1] = x;// 2x for second kind

        for (int i = 0; i < n; ++i) {
            coefficients[i] = 2 * x * coefficients[i - 1] - coefficients[i - 2];
        }

        return coefficients;
    }

    ///@brief calculates a_0...a_{n-1} and saves into the array
    ///@param points - set of N point: waved x_i.
    template<typename F>
    std::vector<F> getA(int n, std::vector<F> &points) {
        //TODO implement formula. std::exp and std::acos can be used.
    }

    ///@brief calculates n points for getA function
    template<typename F>
    std::vector<F> getPoints(int n) {

    }

    template<typename F>
    F expFFT(F x) {
        int precisionValue = 123;//must should be 2^i +- 1

        std::vector<F> points = getPoints<F>(precisionValue);
        //TODO fill array of a_k (formula we can use std::exp and std::acos)
        //TODO use FFT to calculate a_0/2 + sum (a_n * cos(kx))
    }
}

#endif