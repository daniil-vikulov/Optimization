#ifndef FFT_EXP_H
#define FFT_EXP_H

#include <vector>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_complex.h>

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
        for (int i = 0; i < n; i++) {
            F sum_exp_Tk = 0;
            for (int j = 1; j <= n + 1; j++) {
                auto T_k = getT(points[j], n);
                sum_exp_Tk += std::exp(std::acos(points[j])) * T_k[j];
            }
            sum_exp_Tk *= 2;
            sum_exp_Tk /= n + 1;
            coefficients[i] = sum_exp_Tk;
        }
        
        return coefficients;

    }

    ///@brief calculates a_i by integration by parts 
    template<typename F>
    std::vector<F> getA_intergate(int n) {
        std::vector<F> coefficients(n);
        F factor = 2 / Pi<F>;
        F exp_pi = std::exp(Pi<F>);
        coefficients[0] = factor * (exp_pi - 1);
        for (int i = 1; i < n; ++i) {
            coefficients[i] = factor * (-1 + exp_pi * (i % 2)) / (i * i + 1); // formula from wolframalpha
        }

        return coefficients;
    }

    ///@brief calculates n points for getA function -compute x tilda
    template<typename F>
    std::vector<F> getPoints(int n) {
        std::vector<F> x_tilda(n);
        for (int i = 0; i < n; i++) {
            x_tilda[i] = std::cos(Pi<F> * (2 * i - 1) / (2 * n + 1));
        }

        return x_tilda;
    }

    template<typename F>
    ///@brief calculates sum(a[k] * cos(k * x_j)) for all x_j = 2 * pi * j / n, where j = [0, ..., n)
    ///@warning coefficients.size() must be a pow of 2
    ///@return array of sum(x_j): sum(x_j) = result[j].
    std::vector<F> calculateSum(const std::vector<F> &coefficients) {
        size_t dataSize = 2 * coefficients.size();
        auto data = new double[dataSize];

        for (int i = 0; i < coefficients.size(); ++i) {
            data[2 * i] = coefficients[i];
            data[2 * i + 1] = 0.0;
        }

        logI("Data array:");
        for (int i = 0; i < dataSize; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;

        gsl_fft_complex_radix2_forward(data, 1, coefficients.size());

        std::vector<F> result(coefficients.size());
        for (int i = 0; i < result.size(); i += 2) {
            result[i / 2] = data[i];
        }

        logI("Data array:");
        for (int i = 0; i < dataSize; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;

        delete[] data;

        return result;
    }

    template<typename F>
    F expFFT(F x) {
        int precisionValue = 124;//must be a power of two

        auto coefficients = getPoints<F>(precisionValue);

        auto result = calculateSum(getA<F>(precisionValue), coefficients);

        for (int i = 0; i < result.size(); ++i) {
            result[i] += coefficients[0] / 2;
        }

        //TODO return value in a nearest point;
    }
}

#endif
