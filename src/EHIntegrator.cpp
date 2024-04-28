#include "maths/EHIntegrator.h"


using namespace adaai::solution;

EHIntegrator::EHIntegrator(Equation equation, int dimension, int node_number, void *parameters) {
    K = node_number;
    N = dimension;
    B = new double[dimension];
    Parameters = parameters;
}

EHIntegrator::~EHIntegrator() {
    delete[] B;
}

void EHIntegrator::integrate(double *y_0, double *y_prime_0, double t_0, double h) {
    int steps = 15; // TODO should be dynamically calculated (convergence-based)

    for (int i = 0; i < steps; ++i) {
        step(y_0, y_prime_0, t_0, h);
    }
}

void EHIntegrator::step(double *y_0, double *y_prime_0, double t_0, double h) {

}
