#include "physics/AirDensity.h"

#include "physics/Consts.h"
#include "utils/Logger.h"

using namespace adaai::solution;

double AirDensity::operator()(double height) {
    return 0;
}

void AirDensity::calcParams() {

}

double AirDensity::getPressure(double height) {
    double p_0;
    double inLogFunction;
    double inExpValue;
    double t_l;
    double h_l; // layer lower bound
    double r_l; //temperature coefficient

    //for the first layer
    if (height > HEIGHT_1_UPPER_BOUND && height <= HEIGHT_2_UPPER_BOUND) {
        p_0 = P1; // precalculated pressure at the height HEIGHT_1_UPPER_BOUND
        inExpValue = -G * (height - HEIGHT_1_UPPER_BOUND) / R_AIR / T1;
        return P1 * exp(inExpValue);
    }

    if (height <= HEIGHT_1_UPPER_BOUND) {
        p_0 = P0;
        t_l = T0;
        r_l = R_0;
        h_l = 0;
    } else if (height > HEIGHT_2_UPPER_BOUND && height <= HEIGHT_3_UPPER_BOUND) {
        p_0 = P2;
        t_l = T2;
        r_l = R_2;
        h_l = HEIGHT_2_UPPER_BOUND;
    } else {
        p_0 = P3;
        t_l = T3;
        r_l = R_3;
        h_l = HEIGHT_3_UPPER_BOUND;
    }

    inLogFunction = 1.0 - (r_l * (height - h_l) / t_l);
    inExpValue = G / R_AIR / r_l * log(inLogFunction);

    return p_0 * exp(inExpValue);
}
