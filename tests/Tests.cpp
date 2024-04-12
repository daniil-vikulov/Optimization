#include "Tests.h"

#include "physics/DragCoefficients.h"

using namespace adaai;
using namespace solution;

void adaai::tests::printDc() {
    double height = 0.4;

    while (height <= 2.2) {
        logI(DragCoefficients::get(height));

        height += 0.2;
    }
}
