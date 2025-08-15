#include "headers/config.hpp"
#include "headers/tests.hpp"
#include "headers/utils.hpp"
#include "maths/RKF45Integrator.h"
#include <iostream>
#include <vector>

namespace adaai::solution {

int main() {
    // grid for S
    std::vector<double> S(n + 1);
    for (int i = 0; i <= n; ++i) {
        S[i] = i * h;
    }

    std::vector<double> C(n + 1);
    for (int i = 0; i <= n; ++i) {
        C[i] = payoff_function(S[i]);
    }

    RKF45Integrator integrator(black_scholes_equation, n + 1, S.data());
    double tau = 0.0;
    integrator.integrate(C.data(), &tau, T);

    run_tests(C, S);

    return 0;
}

}  // namespace adaai::solution

int main() {
    return adaai::solution::main();
}
