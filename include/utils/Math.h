#ifndef MATH_H
#define MATH_H

#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_math.h>
#include <vector>

namespace adaai::solution {
    ///@brief fеу
    double func(double x, void *params) {
        return exp(x);
    }

    std::vector<std::vector<double>> getChebyshevCoeffs(int n) {
        std::vector<std::vector<double>> coeffs(n + 1, std::vector<double>(n + 1, 0.0));

        gsl_function F;
        F.function = &func;
        F.params = nullptr;

        for (int order = 1; order <= n; order++) {
            gsl_cheb_series *chebSeries = gsl_cheb_alloc(order);

            gsl_cheb_init(chebSeries, &F, -1.0, 1.0); // вычислили ф-ю
            for (int i = 0; i <= order; i++) {
                coeffs[order][i] = gsl_cheb_eval(chebSeries, i); // это у нас a_nk
            }
            gsl_cheb_free(chebSeries);
        }

        return coeffs;
    }

    ///@brief calculates value of Chebyshev polynomial in a specific point
    double getChebApproximation(int n, double x) {
        gsl_function expFunction;

        expFunction.function = func;

        gsl_cheb_series *chebyshevSeries = gsl_cheb_alloc(n);
        gsl_cheb_init(chebyshevSeries, &expFunction, -1.0, 1.0);

        double value = gsl_cheb_eval(chebyshevSeries, x);

        gsl_cheb_free(chebyshevSeries);

        return value;
    }
}


#endif
