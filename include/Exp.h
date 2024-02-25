#ifndef EXP_H
#define EXP_H

#include <cassert>
#include <climits>
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <type_traits>
#include "gsl/gsl_linalg.h"

#include "consts/Consts.h"
#include "consts/GccConsts.h"
#include "utils/Logger.h"
#include "utils/Math.h"

namespace adaai::solution {
    enum class Method {
        Pade,
        Taylor,
        Chebyshev
    };

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

    ///@brief fills array with Chebyshev-based SLE
    void prepareSle(double *matrix, double *column, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i * size + j] = 0;
            }
        }

        for (int k = 0; k < size; ++k) {
            if (k == size - 1) {
                for (int n = 0; n < size; ++n)
                    matrix[k * size + n] = getZeroApproximation(n);
            } else {
                matrix[k * size + k] = -1.0;
                for (int n = k + 1; n < size; ++n) {
                    matrix[k * size + n] = getCoefficient(n, k);
                }
            }
        }

        column[size - 1] = 1.0;
    }

    ///@brief calculates exponent using Chebyshev approximation
    template<typename F>
    F expChebyshev(F x) {
        int size = 21;

        auto matrix = new double[size * size];
        auto column = new double[size];

        prepareSle(matrix, column, size);

        gsl_matrix_view A = gsl_matrix_view_array(matrix, size, size);
        gsl_vector_view b = gsl_vector_view_array(column, size);

        gsl_permutation *permutation = gsl_permutation_alloc(size);
        gsl_vector *answer = gsl_vector_alloc(size);

        int dimension;
        gsl_linalg_LU_decomp(&A.matrix, permutation, &dimension);
        gsl_linalg_LU_solve(&A.matrix, permutation, &b.vector, answer);

        gsl_cheb_series *chebyshevSeries = gsl_cheb_alloc(size - 1);
        chebyshevSeries->c = answer->data;

        chebyshevSeries->c[0] *= 2;

        chebyshevSeries->order = size;
        chebyshevSeries->a = -1;
        chebyshevSeries->b = 1;

        double value = gsl_cheb_eval(chebyshevSeries, (double) x);

        delete[] matrix;
        delete[] column;

        return value;
    }

    ///@brief calculates exponent. Analog to std::exp()
    ///@details uses Pade calculationMethod by default
    template<typename F>
    constexpr F exponent(F x, Method calculationMethod = Method::Chebyshev) {
        static_assert(std::is_floating_point<F>::value,
                      "Not a floating point number");

        if (std::isnan(x)) {
            return x;
        }
        if (x == F(0)) {
            return F(1);
        }

        F intPart;
        F fracPart = std::modf(x, &intPart);

        if (std::abs(fracPart) > F(0.5)) {
            if (x > 0) {
                fracPart -= F(1);
                intPart += F(1);
            } else {
                fracPart += F(1);
                intPart -= F(1);
            }
        }

        if (intPart < static_cast<F>(INT_MIN)) {
            return F(0.0);
        } else if (intPart > static_cast<F>(INT_MAX)) {
            return std::numeric_limits<F>::infinity();
        }

        F y = x / Ln2<F>;
        F yIntPart;
        F yFracPart = std::modf(y, &yIntPart);

        if (std::abs(yFracPart) > F(0.5)) {
            if (y > 0) {
                yFracPart -= F(1);
                yIntPart += F(1);
            } else {
                yFracPart += F(1);
                yIntPart -= F(1);
            }
        }

        if (yIntPart < static_cast<F>(INT_MIN)) {
            return F(0.0);
        } else if (yIntPart > static_cast<F>(INT_MAX)) {
            return std::numeric_limits<F>::infinity();
        }

        F result = std::ldexp(F(1), yIntPart);

        auto temp = yFracPart * Ln2<F>;
        if (calculationMethod == Method::Taylor) {
            constexpr int N = MKExpTaylorOrder<F>();
            result *= expTaylor(temp, N);
        } else if (calculationMethod == Method::Pade) {
            result *= expPade(temp);
        } else if (calculationMethod == Method::Chebyshev) {
            result *= expChebyshev(temp);
        }

        if (result <= 0 && x > 0) {
            return std::numeric_limits<F>::infinity();
        }

        return result;
    }
}

#endif
