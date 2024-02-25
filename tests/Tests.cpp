#include "Tests.h"

#include <sstream>

#include "Exp.h"
#include "Functions.h"

using namespace adaai::solution;
using namespace adaai;

template<typename F>
void testExponentChebyshev(F x) {
    F result = exponent(x, Method::Chebyshev);
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



void tests::testFloatChebyshev() {
    logI("Testing Chebyshev-exponent in float mode...");

    const int count = 10000;
    const float lower_limit = -2147483649.5f;
    const float upper_limit = 2147483648.5f;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        float random_value =
                (static_cast<float>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
                lower_limit;
        testExponentChebyshev<float>(random_value);
    }

    testExponentChebyshev(0.f);
    testExponentChebyshev(1.f);
    testExponentChebyshev(-1.f);
    testExponentChebyshev(1.99999f);
    testExponentChebyshev(-0.456f);
    testExponentChebyshev(10.67f);
    testExponentChebyshev(-15.32f);
    testExponentChebyshev(-std::numeric_limits<float>::infinity());
    testExponentChebyshev(std::numeric_limits<float>::infinity());
    testExponentChebyshev(std::numeric_limits<float>::max());
    testExponentChebyshev(std::numeric_limits<float>::lowest());

    logI("Float mode is tested!!!");
}

void tests::testDoubleChebyshev() {
    logI("Testing Chebyshev-exponent in double mode...");

    const int count = 5000;
    const double lower_limit = -2147483649.5;
    const double upper_limit = 2147483649.5;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        double random_value =
                (static_cast<double>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
                lower_limit;
        testExponentChebyshev<double>(random_value);
    }

    testExponentChebyshev(0.f);
    testExponentChebyshev(1.f);
    testExponentChebyshev(-1.f);
    testExponentChebyshev(1.99999);
    testExponentChebyshev(-0.456);
    testExponentChebyshev(10.67);
    testExponentChebyshev(-15.32);
    testExponentChebyshev(-std::numeric_limits<double>::infinity());
    testExponentChebyshev(std::numeric_limits<double>::infinity());
    testExponentChebyshev(std::numeric_limits<double>::max());
    testExponentChebyshev(std::numeric_limits<double>::lowest());

    logI("Double mode is tested!!!");
}

void tests::testLongDoubleChebyshev() {
    logI("Testing Chebyshev-exponent in long double mode...");

    const int count = 10000;
    const long double lower_limit = -2147483649.5l;
    const long double upper_limit = 2147483649.5l;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count; ++i) {
        long double random_value = (static_cast<long double>(rand()) / RAND_MAX) *
                                   (upper_limit - lower_limit) +
                                   lower_limit;
        testExponentChebyshev<long double>(random_value);
    }

    testExponentChebyshev(0.l);
    testExponentChebyshev(1.l);
    testExponentChebyshev(-1.l);
    testExponentChebyshev(1.99999l);
    testExponentChebyshev(-0.456l);
    testExponentChebyshev(10.67l);
    testExponentChebyshev(-15.32l);
    testExponentChebyshev(-std::numeric_limits<long double>::infinity());
    testExponentChebyshev(std::numeric_limits<long double>::infinity());
    testExponentChebyshev(std::numeric_limits<long double>::max());
    testExponentChebyshev(std::numeric_limits<long double>::lowest());

    logI("Long double mode is tested!!!");
}