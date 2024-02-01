#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>

#include "Logger.h"

template<typename F>
constexpr F Sqrt2 = std::sqrt(F(2));

template<typename F>
constexpr F Ln2 = std::log(F(2)); //TODO нафиг

template<typename F>
constexpr F Eps = std::numeric_limits<F>::epsilon(); //TODO нафиг

template<typename F>
F expTaylor(F x) {
    F sum = 1.0;
    F term = 1.0;
    F curr_eps = Sqrt2<F> * x;
    int n = 1;
    
    while (curr_eps > 10.0 * Eps<F>) {
        term *= x / n;
        sum += term;
        curr_eps *= x / (n+1);
        n++;
    }

    return sum;
}

template<typename F>
F exponent(F x) {
    static_assert(std::is_floating_point<F>::value, "Not a floating point number");

    if (x == F(0)) return F(1);
    if (x == std::numeric_limits<F>::infinity()) return std::numeric_limits<F>::infinity();
    if (x == -std::numeric_limits<F>::infinity()) return F(0);

    F intPart;
    F fracPart = std::modf(x, &intPart);

    if (x < 0 && std::abs(fracPart) > F(0.5)) {
        fracPart -= F(1);
        intPart += F(1);
    }

    F y = x / Ln2<F>;
    F yIntPart;
    F yFracPart = std::modf(y, &yIntPart);

    if (yIntPart > std::numeric_limits<int>::max()) {
        return std::numeric_limits<F>::infinity();
    }

    F result = std::ldexp(F(1), static_cast<int>(yIntPart));

    auto temp = (double) (yFracPart * Ln2<F>);
    result *= expTaylor(temp);

    return result;
}
