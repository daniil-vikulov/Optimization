#ifndef TESTS_HPP
#define TESTS_HPP

#include "black_scholes_analytical.hpp"
#include "black_scholes_numerical.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

namespace adaai::solution {

void run_tests(const std::vector<double> &C, const std::vector<double> &S);

}  // namespace adaai::solution

#endif  // TESTS_HPP
