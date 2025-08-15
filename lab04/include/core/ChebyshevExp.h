#ifndef CHEBYSHEVEXP_H
#define CHEBYSHEVEXP_H

#include <gsl/gsl_linalg.h>

#include "utils/Math.h"
#include "consts/Consts.h"
#include "consts/GccConsts.h"

namespace adaai::solution {
    ///@brief fills array with Chebyshev-based SLE
    void prepareSle(double *matrix, double *column, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i * size + j] = 0;
            }
        }

        for (int k = 0; k < size; ++k) {
            if (k == size - 1) {
                for (int n = 0; n < size; ++n)
                    matrix[k * size + n] = getZeroApproximation(n);
            } else {
                matrix[k * size + k] = -1.0;
                for (int n = k + 1; n < size; ++n) {
                    matrix[k * size + n] = getCoefficient(n, k);
                }
            }
        }

        column[size - 1] = 1.0;
    }

    ///@brief calculates exponent using Chebyshev approximation
    template<typename F>
    F expChebyshev(F x) {
        int size = 21;

        auto matrix = new double[size * size];
        auto column = new double[size];

        prepareSle(matrix, column, size);

        gsl_matrix_view A = gsl_matrix_view_array(matrix, size, size);
        gsl_vector_view b = gsl_vector_view_array(column, size);

        gsl_permutation *permutation = gsl_permutation_alloc(size);
        gsl_vector *answer = gsl_vector_alloc(size);

        int dimension;
        gsl_linalg_LU_decomp(&A.matrix, permutation, &dimension);
        gsl_linalg_LU_solve(&A.matrix, permutation, &b.vector, answer);

        gsl_cheb_series *chebyshevSeries = gsl_cheb_alloc(size - 1);
        chebyshevSeries->c = answer->data;

        chebyshevSeries->c[0] *= 2;

        chebyshevSeries->order = size;
        chebyshevSeries->a = -1;
        chebyshevSeries->b = 1;

        double value = gsl_cheb_eval(chebyshevSeries, (double) x);

        delete[] matrix;
        delete[] column;

        return value;
    }
}

#endif