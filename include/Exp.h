#ifndef EXP_H
#define EXP_H

#include <cassert>
#include <climits>
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <type_traits>

#include "Consts.h"
#include "GccConsts.h"
#include "Logger.h"


namespace adaai::solution {
    enum class MethodE {
        Pade,
        Taylor
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

    ///@brief calculates exponent. Analog to std::exp()
    template<typename F, MethodE M = MethodE::Pade>
    constexpr F exponent(F x) {
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
        if (M == MethodE::Taylor) {
            constexpr int N = MKExpTaylorOrder<F>();
            result *= expTaylor(temp, N);
        } else if (M == MethodE::Pade) {
            result *= expPade(temp);
        }

        if (result <= 0 && x > 0) {
            return std::numeric_limits<F>::infinity();
        }

        return result;
    }
} // namespace adaai::solution

#endif
