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

        Simulator simulator(initialParams, 0.1);
        auto res = simulator.simulate2(10'000);
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

    //logI(initialParams.vX,initialParams.vY);
    Simulator simulator(initialParams, 0.1);
    simulator.simulate(10'000);

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
    (void) (t); // avoid unused parameter warning
    double g = *(double *) params;
    f[0] = y[1];    // dx/dt = vx
    f[1] = 0;       // dvx/dt = 0
    f[2] = y[3];    // dy/dt = vy
    f[3] = -g;      // dvy/dt = -g
    return GSL_SUCCESS;
}

void tests::gslPlayZone() {
// Gravitational acceleration (m/s^2)
    double g = 10.0;

    // Define the system
    gsl_odeiv2_system sys = {func, nullptr, 4, &g};

    // Define initial conditions
    double y[4] = {0, 50, 0, 50}; // Initial position (x=0, y=0) and velocity (vx=50, vy=50)

    double t = 0.0, t1 = 11.0;
    double h = 1e-6; // Initial step size

    // Create a _driver for managing the integration
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rkf45, h, 1e-6, 0.0);

    // Integrate over the time range
    for (double ti = 0.0; ti < t1; ti += 1.0) {
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);

        if (status != GSL_SUCCESS) {
            std::cout << "Error, return value=" << status << std::endl;
            break;
        }

        std::cout << "At time t=" << t << " x=" << y[0] << " vx=" << y[1] << " y=" << y[2] << " vy=" << y[3]
                  << std::endl;
    }

    gsl_odeiv2_driver_free(d);
}

int equation(double t, const double *y, double *func, void *params) {
    func[0] = 1 + y[0] * y[0];

    return 0;
}

void tests::testRKF45() {
    double y[2] = {3, 0};
    RKF45Integrator integrator(equation, 2, nullptr);
    double start = 0;
    integrator.integrate(y, &start, 1);
    logI(y[0], y[1]);
}
