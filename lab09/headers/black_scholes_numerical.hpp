#ifndef BLACK_SCHOLES_NUMERICAL_HPP
#define BLACK_SCHOLES_NUMERICAL_HPP

#include "config.hpp"
#include <vector>

namespace adaai::solution {
double payoff_function(double S);
double upper_boundary(double tau);
int black_scholes_equation(double tau, const double *C, double *dCdtau,
                           void *params);
double linear_interpolate(double S, const std::vector<double> &S_grid,
                          const std::vector<double> &C);

}  // namespace adaai::solution

#endif  // BLACK_SCHOLES_NUMERICAL_HPP
