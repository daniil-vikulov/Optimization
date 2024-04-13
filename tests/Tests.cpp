#include "Tests.h"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include <vector>
#include <cmath>

#include "physics/Consts.h"
#include "physics/Simulator.h"
#include "physics/DragCoefficients.h"
#include "physics/Atmosphere.h"
#include "utils/Logger.h"
#include "maths/RKF45Integrator.h"

using namespace adaai;
using namespace solution;

double gravity(double height) {
    return G / (EARTH_RADIUS + height) / (EARTH_RADIUS + height) * EARTH_RADIUS * EARTH_RADIUS;
}

///@brief function, which controls the simulation
bool stopper(double x, double y, double vX, double vY, double timePast) {
    return y >= 0;
}

struct TimeStamp {
    double time, x, y, vX, vY;
};

std::vector<TimeStamp> trajectoryTelemetry;

///@brief function, which controls the simulation and saves missile's telemetry
bool observer(double x, double y, double vX, double vY, double timePast) {
    trajectoryTelemetry.push_back({timePast, x, y, vX, vY});

    return y > 0;
}

void log() {
    for (auto point: trajectoryTelemetry) {
        if (abs(round(point.time / 5) - point.time / 5) < 0.01) {
            logI(point.x, point.y, point.vX, point.vY);
        }
    }
}

void tests::solution() {
    double resAngle = 0;
    double distance = 0;

    ///Calculates optimal angle
    for (double angle = 0.5; angle < 1.2; angle += 0.05) {
        Simulator::Params initialParams = {};
        initialParams.x = 0;
        initialParams.y = 0;
        initialParams.vX = 1600 * cos(angle);
        initialParams.vY = 1600 * sin(angle);
        initialParams.mass = 120;
        initialParams.csa = M_PI * 0.21 * 0.21 / 4;
        initialParams.airDensity = Atmosphere::getDensity;
        initialParams.gravity = gravity;
        initialParams.dragCoefficient = DragCoefficients::get;
        initialParams.airSpeed = Atmosphere::getAirSpeed;
        initialParams.handler = stopper;

        Simulator simulator(initialParams, 1.0);
        auto res = simulator.simulate(10'000);
        if (distance < res.x) {
            distance = res.x;
            resAngle = angle;
        }
    }
    logI("Optimal angle:", 180.0 / M_PI * resAngle);
    logI("Max distance:", distance);

    ///Simulating best trajectory
    Simulator::Params initialParams = {};
    initialParams.x = 0;
    initialParams.y = 0;
    initialParams.vX = 1600 * cos(resAngle);
    initialParams.vY = 1600 * sin(resAngle);
    initialParams.mass = 120;
    initialParams.csa = M_PI * 0.21 * 0.21 / 4;
    initialParams.airDensity = Atmosphere::getDensity;
    initialParams.gravity = gravity;
    initialParams.dragCoefficient = DragCoefficients::get;
    initialParams.airSpeed = Atmosphere::getAirSpeed;
    initialParams.handler = observer;

    Simulator simulator1(initialParams, 0.1);
    auto res1 = simulator1.simulate(10'000);
    logI(res1.x, res1.y); //Will display 127757 -7.82858
    Simulator simulator2(initialParams, 0.1);
    auto res2 = simulator2.simulate2(10'000);
    logI(res2.x, res2.y); //Will display: 127771 -31.6959

    //log();
}

/////////////////////////////////////////////////////////////////////////////////////////

void adaai::tests::printDc() {
    double height = 0.4;

    while (height <= 4) {
        logI(DragCoefficients::get(height));

        height += 0.2;
    }
}

void tests::printPressure() {
    for (int i = 0; i < 47'000; i += 1000) {
        logI("Height:", i, "    Pressure:", Atmosphere::getPressure(i));
    }
}


void tests::printDensity() {
    for (int i = 0; i < 47'000; i += 1000) {
        logI("Height:", i, "    Density:", Atmosphere::getDensity(i));
    }
}

int func(double t, const double y[], double f[], void *params) {
    f[0] = -2 * y[0] + 4 * y[1] + 3*y[2];
    f[1] = -y[0] + 3 * y[1] - 5*y[2];
    f[2] = y[0] + y[1] - y[2];

    return GSL_SUCCESS;
}

void tests::gslPlayZone() {
// Gravitational acceleration (m/s^2)
    double g = 10.0;

    // Define the system
    gsl_odeiv2_system sys = {func, nullptr, 3, nullptr};

    // Define initial conditions
    double y[3] = {3, -1, 2};

    double t = 0.0, t1 = 1.0;
    double h = 1e-6;

    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rkf45, h, 1e-6, 0.0);

    int status = gsl_odeiv2_driver_apply(d, &t, t1, y);

    if (status != GSL_SUCCESS) {
        std::cout << "Error, return value=" << status << std::endl;
    }

    logI(y[0], y[1], y[2]);

    gsl_odeiv2_driver_free(d);
}

int equation(double t, const double *y, double *func, void *params) {
    func[0] = -2 * y[0] + 4 * y[1] + 3*y[2];
    func[1] = -y[0] + 3 * y[1] - 5*y[2];
    func[2] = y[0] + y[1] - y[2];

    return 0;
}

void tests::testRKF45() {
    double y[3] = {3, -1, 2};
    RKF45Integrator integrator(equation, 3, nullptr);
    double start = 0;
    integrator.integrate(y, &start, 1);
    logI(y[0], y[1], y[2]);
}
