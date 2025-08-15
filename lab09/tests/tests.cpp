#include "../headers/tests.hpp"
#include "../headers/config.hpp"
#include "../headers/utils.hpp"
#include <iostream>

namespace adaai::solution {

void run_tests(const std::vector<double> &C, const std::vector<double> &S) {
    std::vector<double> S_test = {0.9 * K,  0.95 * K, 0.99 * K, K,
                                  1.01 * K, 1.05 * K, 1.1 * K};
    double tol = 1e-2;

    for (double S_val : S_test) {
        double numerical = linear_interpolate(S_val, S, C);
        double analytical = black_scholes_analytical(S_val, K, T, rs, sigmas);
        double error = std::abs(numerical - analytical);

        std::cout << "S = " << S_val << ": Numerical = " << numerical
                  << ", Analytical = " << analytical << ", Error = " << error
                  << std::endl;

        if (error > tol) {
            std::cout << "Test failed at S = " << S_val << std::endl;
        }
    }
}

}  // namespace adaai::solution
