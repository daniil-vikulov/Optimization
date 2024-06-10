#include "maths/EHIntegrator.h"


using namespace adaai::solution;

EHIntegrator::EHIntegrator(const Equation equation, const int dimension, void *parameters) {
    _equation = equation;
    _dimension = dimension;
    _parameters = parameters;
    _b.resize(K);
    _dd.resize(K, std::vector<double>(K));
}


void EHIntegrator::integrate(std::vector<double> &y_0, std::vector<double> &y_prime_0, const double t_0,
                             const double h) {
    constexpr int interations = 15;

    for (int i = 0; i < interations; ++i) {
        step(y_0, y_prime_0, t_0, h);
    }
}

void EHIntegrator::step(std::vector<double> &y_0, std::vector<double> &y_prime_0, double t_0, double h) {
    fillB(y_0, y_prime_0);


}

void EHIntegrator::fillB(std::vector<double> &y, std::vector<double> &y_prime) {
    //TODO calculate _b
}

void EHIntegrator::fillDD(std::vector<double> &y, std::vector<double> &y_prime) {
    //TODO calculate _dd
}
