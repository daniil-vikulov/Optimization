
#include "../headers/utils.hpp"

namespace adaai::solution {
// payoff
double payoff_function(double S) {
    return std::max(S - K, 0.0);
}

// upper boundary condition
double upper_boundary(double tau) {
    double r_val = get_r(tau);
    return S_max - K * std::exp(-r_val * tau);
}

int black_scholes_equation(double tau, const double *C, double *dCdtau,
                           void *params) {
    double *S = static_cast<double *>(params);

    dCdtau[0] = 0.0;  // lower boundary condition

    for (int i = 1; i < n; ++i) {
        double delta_CS = (C[i + 1] - C[i - 1]) / (2 * h);
        double delta2_CS = (C[i + 1] - 2 * C[i] + C[i - 1]) / (h * h);

        double sigma_val = get_sigma(tau);  // step-wise sigma
        double r_val = get_r(tau);          // step-wise r

        dCdtau[i] = 0.5 * sigma_val * sigma_val * S[i] * S[i] * delta2_CS +
                    r_val * S[i] * delta_CS - r_val * C[i];
    }

    dCdtau[n] = upper_boundary(tau);

    return 0;
}

double linear_interpolate(double S, const std::vector<double> &S_grid,
                          const std::vector<double> &C) {
    for (int i = 1; i < S_grid.size(); ++i) {
        if (S_grid[i - 1] <= S && S <= S_grid[i]) {
            double S1 = S_grid[i - 1];
            double S2 = S_grid[i];
            double C1 = C[i - 1];
            double C2 = C[i];
            return C1 + (S - S1) * (C2 - C1) / (S2 - S1);
        }
    }
    return 0.0;
}

}  // namespace adaai::solution