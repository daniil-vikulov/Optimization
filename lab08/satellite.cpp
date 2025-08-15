#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>

#include <iostream>

constexpr size_t OdeOrder = 2;
constexpr size_t Dimension = 3;
constexpr size_t SystemSize = OdeOrder * Dimension;

int gslEquasion(double t, const double y[], double dydt[], void *params) {
    // y[0:2] represents u1(t) = y(t)
    // y[3:5] represents u2(t) = y'(t)

    // For dydt[0:2], simply copy u2(t) to u1'(t)
    for (size_t i = 0; i < Dimension; i++) {
        dydt[i] = y[i + Dimension];
    }
    std::cout << y[0] << y[1] << y[2] << "\n";
    // For dydt[3:5], calculate f(t, u1, u2)
    // Assuming a simple physical model, such as a damped oscillator for each component
    for (size_t i = 0; i < Dimension; i++) {
        dydt[i + Dimension] = -2 * y[i] - 0.5 * y[i + Dimension]; // Example: f = -2*y - 0.5*y'
    }
    return GSL_SUCCESS;
}

void odeiv2Sample() {
    gsl_odeiv2_system system = {gslEquasion, nullptr, SystemSize, nullptr};

    //double t0 = 0.0;
    double h = 1; // 1 second

    double y[SystemSize] = {1.0, 0.0, 0.5, 0.0, 0.0, 0.0}; // Initial conditions for y and y'

    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&system, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);

    for (double t0 = 0.0; t0 < 300000.0; t0 += 1) {
        if (int status = gsl_odeiv2_driver_apply(driver, &t0, t0 + h, y); status != GSL_SUCCESS) {
            std::cerr << "Error, return status=" << status << std::endl;
        }
    }


    gsl_odeiv2_driver_free(driver);
}

int main() {
    odeiv2Sample();
}
