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
        std::vector<F> coefficients(n);
        for(int i = 0; i < n; i++){
            F sum_exp_Tk = 0;
            for(int j = 1;j<n; j++){
                sum_exp_Tk += std::exp(std::acos(points[j])); // * T_k(points[j]))
            }
        }

    }

    ///@brief calculates a_i by integration by parts 
    template<typename F>
    std::vector<F> getA_intergate(int n){
        std::vector<F> coefficients(n);
        F factor = 2 / Pi<F>;
        F exp_pi = std::exp(Pi<F>);
        coefficients[0] = factor * (exp_pi-1);
        for (int i = 1; i < n; ++i) {
            coefficients[i] = factor * (-1 + exp_pi *(i%2)) /(i*i + 1); // formula from wolframalpha
        }

        return coefficients;
    }

    ///@brief calculates n points for getA function -compute x tilda
    template<typename F>
    std::vector<F> getPoints(int n) {
        std::vector<F> x_tilda(n);
        for(int i = 0;i < n; i++) {
            x_tilda[i] = std::cos(Pi<F> * (2*i-1) / (2*n +1));
        }

        return x_tilda;
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
