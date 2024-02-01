#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>

#include "Logger.h"

double factorial(double N) {
    double return_val = 1;

    for (int i = 1; i <= N; i++) {
        return_val = return_val * i;
    }

    return return_val;
}

double E_to_X(double X) {
    double i, e = 0, total = 0;

    for (i = 0; i <= X; ++i) {
        e = pow(X, i) / factorial(X);
        total = total + e;
    }

    return total;
}

template<typename F>
constexpr F Ln2 = std::log(F(2)); // Ln2<double> = 0.693147 (approx)

template<typename F>
constexpr F Eps = std::numeric_limits<F>::epsilon(); // Eps<double> = 2.22045e-16 (approx)

template<typename F>
F Exp(F x) {
    static_assert(std::is_floating_point<F>::value, "Not a floating point number");

    if (x == F(0)) return F(1); // x = 1.0, so this condition is false
    if (x == std::numeric_limits<F>::infinity()) return std::numeric_limits<F>::infinity(); // Not infinity, so false
    if (x == -std::numeric_limits<F>::infinity()) return F(0); // Not negative infinity, so false

    F intPart;
    F fracPart = std::modf(x, &intPart); // For x = 1.0, intPart = 1.0, fracPart = 0.0

    if (x < 0 && std::abs(fracPart) > F(0.5)) {
        fracPart -= F(1); // Not executed for x = 1.0
        intPart += F(1);
    }

    F y = x / Ln2<F>; // y = 1.0 / 0.693147 = 1.4427 (approx)
    F yIntPart;
    F yFracPart = std::modf(y, &yIntPart); // yIntPart = 1.0, yFracPart = 0.4427 (approx)

    if (yIntPart > std::numeric_limits<int>::max()) {
        return std::numeric_limits<F>::infinity(); // Not executed for x = 1.0
    }

    F result = std::ldexp(F(1), static_cast<int>(yIntPart)); // result = 2^1 = 2.0

    auto temp = (double) (yFracPart * Ln2<F>);
    logI(E_to_X(temp), std::exp(temp));
    result *= E_to_X((double) (yFracPart * Ln2<F>)); // result *= e^(0.4427 * 0.693147) = 2.71828 (approx, which is e)

    return result; // returns approximately 2.71828, which is e^1
}

int main() {
    logI("Exp(1.0):", Exp<double>(-1));
    return 0;
}
