#ifndef EXP_H
#define EXP_H

#include <cassert>
#include <climits>
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <type_traits>

#include "consts/Consts.h"
#include "consts/GccConsts.h"
#include "utils/Logger.h"
#include "utils/Math.h"
#include "utils/SleSolver.h"

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

    void prepareChebSle(std::vector<std::vector<double>> &matrix, std::vector<double> &column, int N) {
        //TODO BUG HAZARD!!!
        auto a = getChebyshevCoeffs(N);

        matrix.resize(N + 1, std::vector<double>(N + 1, 0.0));
        column.resize(N + 1, 0.0);

        //setup column:
        for (int i = 0; i < column.size() - 1; ++i) {
            column[i] = 0;
        }
        column[column.size() - 1] = 1;

        //setup N-1 equations
        for (int k = 0; k < N - 1; ++k) {
            for (int n = k + 1; n < N; ++n) {
                matrix[k][n] = a[n][k];
            }

            matrix[k][k] = -1;
        }

        //specifying Cauchy equation
        for (int i = 0; i < N; ++i) {
            matrix[N][i] = getChebApproximation(i, 0);
        }

    }

    ///@brief calculates exponent using Chebyshev approximation
    template<typename F>
    F expChebyshev(F x) {
        int n = 5;
        auto value = (double) x;

        std::vector<std::vector<double>> matrix;
        std::vector<double> column;

        prepareChebSle(matrix, column, n);

        std::vector<double> coeffs = sleSolve(matrix, column);

        double res = 0.0;

        for (int i = 0; i <= n; ++i) {
            res += getChebApproximation(i, value) * coeffs[i];
        }

        return (F) res;
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
} // namespace adaai::solution

#endif
