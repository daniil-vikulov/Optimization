#ifndef MATH_H
#define MATH_H

#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_math.h>
#include <vector>

namespace adaai::solution {
    ///@brief genate
    template<typename F>
    std::vector<std::vector<F>> getChebyshevCoeffs(int n) {
        //TODO
    }

    ///@brief fеу
    double func(double x, void *params) {
        return exp(x);
    }

    ///@brief calculates value of Chebyshev polynomial in a specific point
    template<typename F>
    F getChebApproximation (int n, F x) {
        gsl_function expFunction;

        expFunction.function = func;

        gsl_cheb_series *chebyshevSeries = gsl_cheb_alloc(n);
        gsl_cheb_init(chebyshevSeries, &expFunction, -1.0, 1.0);

        F value = gsl_cheb_eval(chebyshevSeries, x);

        gsl_cheb_free(chebyshevSeries);

        return value;
    }
}



#endif
