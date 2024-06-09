#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "utils.hpp"
#include <cmath>
#include <vector>

namespace adaai::solution {

const double K = 100.0;
const int n = 500;
const int N = 5;
const double T = 1.0;
const double sigma_max = 0.26;
const double S_max = K * std::exp(N * sigma_max * std::sqrt(T));
const double h = S_max / n;
const std::vector<double> rs = {0.16, 0.15, 0.14, 0.1};
const std::vector<double> sigmas = {0.25, 0.23, 0.26, 0.24};

}  // namespace adaai::solution

#endif  // CONFIG_HPP
