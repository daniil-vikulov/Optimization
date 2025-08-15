#include "../headers/utils.hpp"
#include <gsl/gsl_cdf.h>

namespace adaai::solution {
double black_scholes_analytical(double S, double K, double T,
                                const std::vector<double> &rs,
                                const std::vector<double> &sigmas) {

    double sum_r = 0.0;
    double sum_sigma_2 = 0.0;

    for (size_t i = 0; i < rs.size(); ++i) {
        sum_r += rs[i];
        sum_sigma_2 += sigmas[i] * sigmas[i];
    }

    double numerator_plus = std::log(S / K) + sum_r / rs.size();
    double numerator_diff = sum_sigma_2 / (2 * rs.size());
    double denominator = std::sqrt(sum_sigma_2 / rs.size());
    double d1 = (numerator_plus + numerator_diff) / denominator;
    double d2 = (numerator_plus - numerator_diff) / denominator;

    return S * gsl_cdf_gaussian_P(d1, 1.0) -
           K * std::exp(-sum_r / rs.size()) * gsl_cdf_gaussian_P(d2, 1.0);

    // double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) /
    //             (sigma * std::sqrt(T));
    // double d2 = d1 - sigma * std::sqrt(T);
    // return S * gsl_cdf_gaussian_P(d1, 1.0) -
    //        K * std::exp(-r * T) * gsl_cdf_gaussian_P(d2, 1.0);
}
}  // namespace adaai::solution