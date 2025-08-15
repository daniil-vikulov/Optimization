#ifndef EXP_H
#define EXP_H

#include <cassert>
#include <limits>
#include <type_traits>

#include "core/ChebyshevExp.h"
#include "core/FFTExp.h"
#include "core/PadeExp.h"
#include "core/TaylorExp.h"

namespace adaai::solution {
    enum class Method {
        Pade,
        Taylor,
        Chebyshev,
        FFT
    };

    ///@brief calculates exponent. Analog to std::exp()
    ///@details uses Pade calculationMethod by default
    template<typename F>
    constexpr F exponent(F x, Method calculationMethod = Method::FFT) {
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
        } else if (calculationMethod == Method::FFT) {
            result *= expFFT(temp);
        }

        if (result <= 0 && x > 0) {
            return std::numeric_limits<F>::infinity();
        }

        return result;
    }
}

#endif
