#include "physics/Simulator.h"

#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "maths/RKF45Integrator.h"

#include "physics/Atmosphere.h"
#include "utils/Logger.h"

using namespace adaai::solution;

Simulator::Simulator(Simulator::Params initialParams, double timeStep) {
    _timeStep = timeStep;
    _params = initialParams;

}

Simulator::Params Simulator::simulate(double endTime) {
    arr[0] = _params.x;
    arr[1] = _params.vX;
    arr[2] = _params.y;
    arr[3] = _params.vY;

    gsl_odeiv2_system system = {function, nullptr, 4, &_params};
    auto driver = gsl_odeiv2_driver_alloc_y_new(&system, gsl_odeiv2_step_rkf45, _timeStep, 1e-6, 0.0);
    double t = _params.time;

    while (t < endTime) {
        int status = gsl_odeiv2_driver_apply(driver, &t, t + _timeStep, arr);
        if (status != GSL_SUCCESS) {
            logE("Error occurred while integrating with status code:", status);
            break;
        }

        _params.x = arr[0];
        _params.vX = arr[1];
        _params.y = arr[2];
        _params.vY = arr[3];
        _params.time = t;

        if (!_params.handler(_params.x, _params.y, _params.vX, _params.vY, _params.time)) {
            break;
        }
    }

    gsl_odeiv2_driver_free(driver);

    return _params;
}

Simulator::Params Simulator::simulate2(double endTime) {
    arr[0] = _params.x;
    arr[1] = _params.vX;
    arr[2] = _params.y;
    arr[3] = _params.vY;

    RKF45Integrator integrator(function, 4, &_params);
    double t = _params.time;

    integrator.integrate(arr, &t, t + _timeStep);

    _params.x = arr[0];
    _params.vX = arr[1];
    _params.y = arr[2];
    _params.vY = arr[3];
    _params.time = t;

    while (t < endTime) {
        integrator.integrate(arr, &t, t + _timeStep);

        _params.x = arr[0];
        _params.vX = arr[1];
        _params.y = arr[2];
        _params.vY = arr[3];
        _params.time = t;

        if (!_params.handler(_params.x, _params.y, _params.vX, _params.vY, _params.time)) {
            break;
        }
    }

    return _params;
}

int Simulator::function(double t, const double *arr, double *funcs, void *parameters) {
    Params params = *(Params *) parameters;

    double vX = arr[1];
    double y = arr[2];
    double vY = arr[3];

    double csa = params.csa;
    double m = params.mass;

    double g = 0;
    double dc = 0;
    double ad = 0;

    if (params.gravity) g = params.gravity(y);
    if (params.dragCoefficient) dc = params.dragCoefficient(sqrt((vX * vX + vY * vY)) / Atmosphere::getAirSpeed(y));
    if (params.airDensity) ad = params.airDensity(y);

    double v2 = vX * vX + vY * vY;
    double v = sqrt(v2);

    double dragForce = ad * dc * csa * v2;

    funcs[0] = vX;
    funcs[1] = -dragForce * vX / v / m;
    funcs[2] = vY;
    funcs[3] = -dragForce * vY / v / m - g;

    return GSL_SUCCESS;
}
