#include "physics/DragCoefficients.h"

#include <cmath>

#include "utils/Logger.h"

using namespace adaai::solution;

double DragCoefficients::get(double speed) {
    if (speed < Speed[0]) {
        logF("Under speeding");
    }

    for (int i = 0; i < Size - 1; ++i) {
        if (Speed[i] <= speed && Speed[i + 1] > speed) {
            return interpolate(i, speed);
        }
    }

    double a = 1;
    double b = 2.2;
    double c = 0.37;
    double d = 0.22;
    double y = pow(c / d, 1 / (a - b));
    double x = c / pow(y, a);

    return x* pow(y, speed);
}


double DragCoefficients::interpolate(int index, double speed) {
    double x1 = Speed[index];
    double y1 = Value[index];
    double x2 = Speed[index + 1];
    double y2 = Value[index + 1];

    double k = (y2 - y1) / (x2 - x1);
    double b = (x2 * y1 - x1 * y2) / (x2 - x1);

    return k * speed + b;
}
