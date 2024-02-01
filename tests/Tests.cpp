#include "Tests.h"

#include "Exp.hpp"

void tests::printExp() {
    float floatValue = 1.0f;
    double doubleValue = 1.0;
    long double longDoubleValue = 1.0l;
    logI("Float:", exponent(floatValue));
    logI("Double:", exponent(floatValue));
    logI("Long double:", exponent(floatValue));
}