#ifndef EXP_H
#define EXP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>
#include <type_traits>
#include <climits>

#include "Logger.h"
#include "Consts.h"
#include "GccConsts.h"

namespace adaai::solution {
    template<typename F>
    F expTaylor(F x) {
        F sum = 1.0;
        F term = 1.0;
        F curr_eps = x;
        int n = 1;

        if (x > 0) {
            curr_eps *= Sqrt2<F>;
        }

        while (std::abs(curr_eps) > 10.0 * Eps<F>) {
            term *= x / n;
            sum += term;
            curr_eps *= x / (n + 1);
            n++;
        }

        return sum;
    }

    template<typename F>
    constexpr F exponent(F x) {
        static_assert(std::is_floating_point<F>::value, "Not a floating point number");

        if (std::isnan(x)) {
            return x;
        }
        if (x == F(0)) return F(1);

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

        if (intPart < INT_MIN) {
            return F(0.0);
        } else if (intPart > INT_MAX) {
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

        if (yIntPart < INT_MIN) {
            return F(0.0);
        } else if (yIntPart > INT_MAX) {
            return std::numeric_limits<F>::infinity();
        }

        F result = std::ldexp(F(1), static_cast<int>(yIntPart));

        auto temp = yFracPart * Ln2<F>;

        result *= expTaylor(temp);

        return result;
    }
}

#endif