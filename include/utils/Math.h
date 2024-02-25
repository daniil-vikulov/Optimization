#ifndef MATH_H
#define MATH_H

#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_math.h>
#include <vector>

namespace adaai::solution {
    ///@brief
    double getCoefficient(int n, int k) {
        return (k & 1) == (n & 1) ? 0 : ((n & 1) == 1 && k == 0) ? n : 2 * n;
    }

    ///@brief calculates value of Chebyshev-s polynomial in zero point
    constexpr int getZeroApproximation(int n) {
        return (n & 1) == 1 ? 0 : ((n & 3) == 0) ? 1 : -1;
    }

    double calculateChebyshevSeries() {

    }
}


#endif
