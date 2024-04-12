#include "Tests.h"

#include "physics/DragCoefficients.h"
#include "physics/AirDensity.h"

using namespace adaai;
using namespace solution;

void adaai::tests::printDc() {
    double height = 0.4;

    while (height <= 2.2) {
        logI(DragCoefficients::get(height));

        height += 0.2;
    }
}

void tests::printPressure() {
    for (int i = 0; i < 47'000; i+=1000) {
        logI("Height:", i, "    Pressure:", AirDensity::getPressure(i));
    }
}


void tests::printDensity() {
    for (int i = 0; i < 47'000; i+=1000) {
        logI("Height:", i, "    Pressure:", AirDensity::get(i));
    }
}
