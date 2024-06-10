#include "maths/EHIntegrator.h"

#include <cmath>

using namespace adaai::solution;

EHIntegrator::EHIntegrator(const Equation equation, const int dimension, void *parameters) {
    _equation = equation;
    _dimension = dimension;
    _parameters = parameters;
    _b.resize(K);
    _dd.resize(K, std::vector(K, std::vector<double>(_dimension)));
    _yInNodes.resize(K, std::vector<double>(_dimension));
    _yPrimeInNodes.resize(K, std::vector<double>(_dimension));
}

void EHIntegrator::integrate(std::vector<double> &y0, std::vector<double> &yPrime0, const double t0,
                             const double h) {
    constexpr int interations = 15; //TODO make dynamic

    std::copy(y0.begin(), y0.end(), _yInNodes[0].begin());
    std::copy(yPrime0.begin(), yPrime0.end(), _yPrimeInNodes[0].begin());

    for (int i = 0; i < interations; ++i) {
        step(t0, h);
    }

    std::copy(_yInNodes[K - 1].begin(), _yInNodes[K - 1].end(), y0.begin());
    std::copy(_yPrimeInNodes[K - 1].begin(), _yPrimeInNodes[K - 1].end(), yPrime0.begin());
}

void EHIntegrator::step(const double t0, const double h) {
    fillB(t0);

    for (int i = 1; i < K; ++i) {
        for (int j = 0; j < _dimension; ++j) {
            _yPrimeInNodes[i][j] = _yPrimeInNodes[0][j];
            for (int k = 0; k < K; ++k) {
                _yPrimeInNodes[i][j] += _b[k][i] * std::pow(h * i, k + 1) / (k + 1);
            }
        }
    }

    for (int i = 1; i < K; ++i) {
        for (int j = 0; j < _dimension; ++j) {
            _yInNodes[i][j] = -_yInNodes[0][j] + _yPrimeInNodes[i][j];
            for (int k = 0; k < K; ++k) {
                _yInNodes[i][j] += _b[k][i] * std::pow(h * i, k + 2) / (k + 1) / (k + 2);
            }
        }
    }
}

void EHIntegrator::fillB(const double t0) {
    fillDD(t0);

    //TODO calculate _b
}

void EHIntegrator::fillDD(const double t0) {
    for (int j = 0; j < K; ++j) {
        _dd[j][0] = _equation(t0, _yInNodes[j], _yPrimeInNodes[j], nullptr);
    }

    for (int order = 1; order < K; ++order) {
        for (int nodeIndex = 0; nodeIndex < K; ++nodeIndex) {
            for (int dim = 0; dim < _dimension; ++dim) {
                _dd[nodeIndex][order][dim] = (_dd[nodeIndex + 1][order - 1][dim] - _dd[nodeIndex][order - 1][dim]) /
                                             order;
            }
        }
    }
}
