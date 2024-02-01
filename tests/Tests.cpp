#include "Tests.h"

#include "Exp.h"

template<typename T>
bool areEqual(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 100) {
    T diff = std::abs(a - b);
    if (diff <= epsilon) {
        return true;
    }

    T absA = std::abs(a);
    T absB = std::abs(b);
    T largest = (absB > absA) ? absB : absA;

    if (diff <= largest * epsilon) {
        return true;
    }

    return false;
}

template<typename F>
void testExponent(F x) {
    F result = exponent(x);
    F expected = std::exp(x);
    if (!areEqual(result, expected)) {
        logF("Test failed:", result, "is not equal to", expected);
    }
}

void tests::testFloat() {
    logI("Testing exponent in float mode...");

    testExponent<float>(0);
    testExponent<float>(1);
    testExponent<float>(-1);
    testExponent<float>(0.5f);
    testExponent<float>(-0.5f);
    testExponent<float>(10.0f);
    testExponent<float>(-10.0f);
    testExponent<float>(std::numeric_limits<float>::max());
    testExponent<float>(std::numeric_limits<float>::lowest());

    logI("Float mode is tested!!!");
}

void tests::testDouble() {
    logI("Testing exponent in double mode...");

    testExponent<double>(0);
    testExponent<double>(1);
    testExponent<double>(-1);
    testExponent<double>(0.5);
    testExponent<double>(-0.5);
    testExponent<double>(10.0);
    testExponent<double>(-10.0);
    testExponent<double>(std::numeric_limits<double>::max());
    testExponent<double>(std::numeric_limits<double>::lowest());

    logI("Double mode is tested!!!");
}

void tests::testLongDouble() {
    logI("Testing exponent in long double mode...");

    testExponent<long double>(0);
    testExponent<long double>(1);
    testExponent<long double>(-1);
    testExponent<long double>(0.5L);
    testExponent<long double>(-0.5L);
    testExponent<long double>(10.0L);
    testExponent<long double>(-10.0L);
    testExponent<long double>(std::numeric_limits<long double>::max());
    testExponent<long double>(std::numeric_limits<long double>::lowest());

    logI("Long double mode is tested!!!");
}


