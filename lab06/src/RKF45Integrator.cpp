#include "maths/RKF45Integrator.h"

#include <cstring>
#include <vector>
#include <cmath>

#include "utils/Logger.h"

using namespace adaai::solution;

RKF45Integrator::RKF45Integrator(Equation equation, int n, void *params) {
    _n = n;
    _equation = equation;
    _parameters = params;
    k1 = new double[n];
    k2 = new double[n];
    k3 = new double[n];
    k4 = new double[n];
    k5 = new double[n];
    k6 = new double[n];
    buf = new double[n];
}

RKF45Integrator::~RKF45Integrator() {
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete[] k5;
    delete[] k6;
    delete[] buf;
}

void RKF45Integrator::integrate(double *y, double *tStart, double tEnd) {
    double t = *tStart;

    double dt = 1e-2;
    while (t < tEnd) {
        dt = std::min(dt, tEnd - t);
        if (step(t, dt, y)) {
            t += dt;
        }
    }

    *tStart = t;
}

bool RKF45Integrator::step(double t, double &h, double *y) {
    ///filling k1
    memcpy(buf, y, _n * sizeof(double));
    _equation(t + A[1] * h, buf, k1, _parameters);
    for (int i = 0; i < _n; ++i) {
        k1[i] *= h;
    }

    ///filling k2
    memcpy(buf, y, _n * sizeof(double));
    for (int i = 0; i < _n; ++i) {
        buf[i] += h * B[2][1] * k1[i];
    }
    _equation(t + A[2] * h, buf, k2, _parameters);
    for (int i = 0; i < _n; ++i) {
        k2[i] *= h;
    }

    ///filling k3
    memcpy(buf, y, _n * sizeof(double));
    for (int i = 0; i < _n; ++i) {
        buf[i] += h * (B[3][1] * k1[i] + B[3][2] * k2[i]);
    }
    _equation(t + A[3] * h, buf, k3, _parameters);
    for (int i = 0; i < _n; ++i) {
        k3[i] *= h;
    }

    ///filling k4
    memcpy(buf, y, _n * sizeof(double));
    for (int i = 0; i < _n; ++i) {
        buf[i] += h * (B[4][1] * k1[i] + B[4][2] * k2[i] + B[4][3] * k3[i]);
    }
    _equation(t + A[4] * h, buf, k4, _parameters);
    for (int i = 0; i < _n; ++i) {
        k4[i] *= h;
    }

    ///filling k5
    memcpy(buf, y, _n * sizeof(double));
    for (int i = 0; i < _n; ++i) {
        buf[i] += h * (B[5][1] * k1[i] + B[5][2] * k2[i] + B[5][3] * k3[i] + B[5][4] * k4[i]);
    }
    _equation(t + A[5] * h, buf, k5, _parameters);
    for (int i = 0; i < _n; ++i) {
        k5[i] *= h;
    }

    ///filling k6
    memcpy(buf, y, _n * sizeof(double));
    for (int i = 0; i < _n; ++i) {
        buf[i] += h * (B[6][1] * k1[i] + B[6][2] * k2[i] + B[6][3] * k3[i] + B[6][4] * k4[i] + B[6][5] * k5[i]);
    }
    _equation(t + A[6] * h, buf, k6, _parameters);
    for (int i = 0; i < _n; ++i) {
        k6[i] *= h;
    }

    ///back-upping y
    double y_initial[_n];
    memcpy(y_initial, y, _n * sizeof(double));

    for (int i = 0; i < _n; ++i) {
        y[i] += Gamma[1] * k1[i] + Gamma[2] * k2[i] + Gamma[3] * k3[i] + Gamma[4] * k4[i] + Gamma[5] * k5[i] +
                Gamma[6] * k6[i];
    }

    ///calculating delta vector
    double delta_vector[_n];
    for (int i = 0; i < _n; ++i) {
        delta_vector[i] = h * (Sigma[1] * k1[i] + Sigma[2] * k2[i] + Sigma[3] * k3[i] + Sigma[4] * k4[i] +
                               Sigma[5] * k5[i] + Sigma[6] * k6[i]);
    }

    ///calculating error (delta)
    double delta = 0;
    for (int i = 0; i < _n; ++i) {
        delta = std::max(std::abs(delta_vector[i]), delta);
    }


    h = 0.9 * h * std::pow(Tolerance / delta, 1.0 / 5.0);
    if (delta < Tolerance) {
        return true;
    } else {
        memcpy(y, y_initial, _n * sizeof(double));
        return false;
    }
}
