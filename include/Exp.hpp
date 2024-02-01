#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>

#include "Logger.h"

template<typename F>
F expTaylor(F x, int n) {
    F sum = 1.0;
    F term = 1.0;

    for (int i = 1; i <= n; ++i) {
        term *= x / i;
        sum += term;
    }

    return sum;
}

template<typename F>
constexpr F Ln2 = std::log(F(2)); //TODO нафиг

template<typename F>
constexpr F Eps = std::numeric_limits<F>::epsilon(); //TODO нафиг

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
    result *= expTaylor(temp, 10);

    return result;
}