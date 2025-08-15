#ifndef BLACK_SCHOLES_ANALYTICAL_HPP
#define BLACK_SCHOLES_ANALYTICAL_HPP

#include "config.hpp"
#include <vector>

namespace adaai::solution {

double black_scholes_analytical(double S, double K, double T,
                                const std::vector<double> &rs,
                                const std::vector<double> &sigmas);

}  // namespace adaai::solution

#endif  // BLACK_SCHOLES_ANALYTICAL_HPP
