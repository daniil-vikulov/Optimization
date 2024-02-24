#ifndef SLE_SOLVER_H
#define SLE_SOLVER_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <vector>

#include "Logger.h"

namespace adaii::solution {
    ///@brief solves system of linear equations. formula: AX = V
    ///@param A matrix of coefficients
    ///@param V vector of known values
    ///@return X - vector of unknown variables: (x_1, ..., x_n)
    template<typename T>
    std::vector<T> sleSolve(const std::vector<std::vector<T>> &A, const std::vector<T> &V) {
        size_t N = V.size();

        if (V.size() != A.size() || A.size() != A[0].size()) {
            logF("Dimension mismatch");
        }

        gsl_matrix *gslA = gsl_matrix_alloc(N, N);
        gsl_vector *gslV = gsl_vector_alloc(N);
        gsl_vector *gslX = gsl_vector_alloc(N);
        gsl_permutation *p = gsl_permutation_alloc(N);

        for (size_t i = 0; i < N; ++i) {
            gsl_vector_set(gslV, i, V[i]);
            for (size_t j = 0; j < N; ++j) {
                gsl_matrix_set(gslA, i, j, A[i][j]);
            }
        }

        int s;

        gsl_linalg_LU_decomp(gslA, p, &s);
        gsl_linalg_LU_solve(gslA, p, gslV, gslX);

        std::vector<T> X(N);
        for (size_t i = 0; i < N; ++i) {
            X[i] = gsl_vector_get(gslX, i);
        }

        gsl_matrix_free(gslA);
        gsl_vector_free(gslV);
        gsl_vector_free(gslX);
        gsl_permutation_free(p);

        return X;
    }
}

#endif
