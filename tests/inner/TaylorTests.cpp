#include "TaylorTests.h"

#include "../Functions.h"
#include "utils/Logger.h"
#include "Exp.h"

using namespace adaai;
using namespace adaai::solution;
using namespace adaai::tests;

template<typename F>
void testExponentTaylor(F x) {
    F result = exponent(x, Method::Taylor);
    F expected = std::exp(x);
    if (std::isnan(result)) {
        if (!std::isnan(expected)) {
            logF("Nan test failed:", result, "is not equal to", expected,
                 "for value:", x);
        } else {
            logI("Test passed: all is nan");
        }
        return;
    }
    if (x <= 0) {
        if (!tests::areEqualNegative(result, expected)) {
            logF("Negative test failed:", result, "is not equal to", expected,
                 "for value:", x);
        }
    } else {
        if (!tests::areEqualPositive(result, expected)) {
            logF("Positive test failed:", result, "is not equal to", expected,
                 "for value:", x);
        }
    }
}

void inner::testFloatTaylor() {
    logI("Testing Taylor-exponent in float mode...");

    const int count = 100000000;
    const float lower_limit = -2147483649.5f;
    const float upper_limit = 2147483648.5f;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        float random_value =
                (static_cast<float>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
                lower_limit;
        testExponentTaylor<float>(random_value);
    }

    testExponentTaylor(0.f);
    testExponentTaylor(1.f);
    testExponentTaylor(-1.f);
    testExponentTaylor(1.99999f);
    testExponentTaylor(-0.456f);
    testExponentTaylor(10.67f);
    testExponentTaylor(-15.32f);
    testExponentTaylor(-std::numeric_limits<float>::infinity());
    testExponentTaylor(std::numeric_limits<float>::infinity());
    testExponentTaylor(std::numeric_limits<float>::max());
    testExponentTaylor(std::numeric_limits<float>::lowest());

    logI("Float mode is tested!!!");
}

void inner::testDoubleTaylor() {
    logI("Testing Taylor-exponent in double mode...");

    const int count = 50000000;
    const double lower_limit = -2147483649.5;
    const double upper_limit = 2147483649.5;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        double random_value =
                (static_cast<double>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
                lower_limit;
        testExponentTaylor<double>(random_value);
    }

    testExponentTaylor(0.f);
    testExponentTaylor(1.f);
    testExponentTaylor(-1.f);
    testExponentTaylor(1.99999);
    testExponentTaylor(-0.456);
    testExponentTaylor(10.67);
    testExponentTaylor(-15.32);
    testExponentTaylor(-std::numeric_limits<double>::infinity());
    testExponentTaylor(std::numeric_limits<double>::infinity());
    testExponentTaylor(std::numeric_limits<double>::max());
    testExponentTaylor(std::numeric_limits<double>::lowest());

    logI("Double mode is tested!!!");
}

void inner::testLongDoubleTaylor() {
    logI("Testing Taylor-exponent in long double mode...");

    const int count = 10000000;
    const long double lower_limit = -2147483649.5l;
    const long double upper_limit = 2147483649.5l;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        long double random_value = (static_cast<long double>(rand()) / RAND_MAX) *
                                   (upper_limit - lower_limit) +
                                   lower_limit;
        testExponentTaylor<long double>(random_value);
    }

    testExponentTaylor(0.l);
    testExponentTaylor(1.l);
    testExponentTaylor(-1.l);
    testExponentTaylor(1.99999l);
    testExponentTaylor(-0.456l);
    testExponentTaylor(10.67l);
    testExponentTaylor(-15.32l);
    testExponentTaylor(-std::numeric_limits<long double>::infinity());
    testExponentTaylor(std::numeric_limits<long double>::infinity());
    testExponentTaylor(std::numeric_limits<long double>::max());
    testExponentTaylor(std::numeric_limits<long double>::lowest());

    logI("Long double mode is tested!!!");
}