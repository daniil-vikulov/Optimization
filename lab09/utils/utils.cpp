#include "../headers/utils.hpp"
#include <algorithm>
#include <cmath>
#include <gsl/gsl_cdf.h>

namespace adaai::solution {

double get_sigma(double tau) {
    if (tau < 0.25) {
        return 0.25;
    } else if (tau < 0.5) {
        return 0.23;
    } else if (tau < 0.75) {
        return 0.26;
    } else {
        return 0.24;
    }
}

double get_r(double tau) {
    if (tau < 0.25) {
        return 0.16;
    } else if (tau < 0.5) {
        return 0.15;
    } else if (tau < 0.75) {
        return 0.14;
    } else {
        return 0.1;
    }
}

}  // namespace adaai::solution