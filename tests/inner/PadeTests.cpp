#include "PadeTests.h"

#include "Exp.h"
#include "../Functions.h"

using namespace adaai;
using namespace adaai::solution;
using namespace adaai::tests;

template<typename F>
void testExponentPade(F x) {
    F result = exponent(x, Method::Pade);
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

void inner::testFloatPade() {
    logI("Testing Pade-exponent in float mode...");

    const int count = 100000000;
    const float lower_limit = -2147483649.5f;
    const float upper_limit = 2147483648.5f;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        float random_value =
                (static_cast<float>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
                lower_limit;
        testExponentPade<float>(random_value);
    }

    testExponentPade(0.f);
    testExponentPade(1.f);
    testExponentPade(-1.f);
    testExponentPade(1.99999f);
    testExponentPade(-0.456f);
    testExponentPade(10.67f);
    testExponentPade(-15.32f);
    testExponentPade(-std::numeric_limits<float>::infinity());
    testExponentPade(std::numeric_limits<float>::infinity());
    testExponentPade(std::numeric_limits<float>::max());
    testExponentPade(std::numeric_limits<float>::lowest());

    logI("Float mode is tested!!!");
}

void inner::testDoublePade() {
    logI("Testing Pade-exponent in double mode...");

    const int count = 50000000;
    const double lower_limit = -2147483649.5;
    const double upper_limit = 2147483649.5;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        double random_value =
                (static_cast<double>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
                lower_limit;
        testExponentPade<double>(random_value);
    }

    testExponentPade(0.f);
    testExponentPade(1.f);
    testExponentPade(-1.f);
    testExponentPade(1.99999);
    testExponentPade(-0.456);
    testExponentPade(10.67);
    testExponentPade(-15.32);
    testExponentPade(-std::numeric_limits<double>::infinity());
    testExponentPade(std::numeric_limits<double>::infinity());
    testExponentPade(std::numeric_limits<double>::max());
    testExponentPade(std::numeric_limits<double>::lowest());

    logI("Double mode is tested!!!");
}

void inner::testLongDoublePade() {
    logI("Testing Pade-exponent in long double mode...");

    const int count = 10000000;
    const long double lower_limit = -2147483649.5l;
    const long double upper_limit = 2147483649.5l;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        long double random_value = (static_cast<long double>(rand()) / RAND_MAX) *
                                   (upper_limit - lower_limit) +
                                   lower_limit;
        testExponentPade<long double>(random_value);
    }

    testExponentPade(0.l);
    testExponentPade(1.l);
    testExponentPade(-1.l);
    testExponentPade(1.99999l);
    testExponentPade(-0.456l);
    testExponentPade(10.67l);
    testExponentPade(-15.32l);
    testExponentPade(-std::numeric_limits<long double>::infinity());
    testExponentPade(std::numeric_limits<long double>::infinity());
    testExponentPade(std::numeric_limits<long double>::max());
    testExponentPade(std::numeric_limits<long double>::lowest());

    logI("Long double mode is tested!!!");
}