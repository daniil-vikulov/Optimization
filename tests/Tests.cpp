#include "Tests.h"

#include <gsl/gsl_sf_bessel.h>

#include "utils/Logger.h"
#include "inner/TaylorTests.h"
#include "inner/PadeTests.h"

using namespace adaai;
using namespace adaai::solution;
using namespace adaai::tests::inner;

void tests::testGslLib() {
    double y = gsl_sf_bessel_J0(5.0);
    logI("J0(5) =", y);
}

void tests::testPade() {
    testFloatPade();
    testDoublePade();
    testLongDoublePade();
}

void tests::testTaylor() {
    testFloatTaylor();
    testDoubleTaylor();
    testLongDoubleTaylor();
}