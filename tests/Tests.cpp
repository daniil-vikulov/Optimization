#include "Tests.h"

#include "Exp.h"

template<typename T>
bool areEqualNegative(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 600) {
    // if ()
    if (std::isinf(a)) {
        if (std::isinf(b)) {
            return true;
        } else {
            return false;
        }
    }
    T diff = std::abs(a - b);
    if (diff <= epsilon) {
        return true;
    }

    return false;
}

template<typename T>
bool areEqualPositive(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 600) {
    if (std::isinf(a)) {
        if (std::isinf(b)) {
            return true;
        } else {
            return false;
        }
    }
    T err = std::abs(a / b - 1.0);
    if (err <= epsilon) {
        return true;
    }

    return false;
}

template<typename F>
void testExponent(F x) {
    F result = exponent(x);
    F expected = std::exp(x);
    if (x <= 0) {
        if (!areEqualNegative(result, expected)) {
            logF("Test failed:", result, "is not equal to", expected);
        }
    
    } else {
        if (!areEqualPositive(result, expected)) {
            logF("Test failed:", result, "is not equal to", expected);
    }
    }

}

void tests::testFloat() {
    logI("Testing exponent in float mode...");

    testExponent<float>(0);
    testExponent<float>(1);
    testExponent<float>(-1);
    testExponent<float>(1.99999f);
    testExponent<float>(-0.456f);
    testExponent<float>(10.67f);
    testExponent<float>(-10.32f);
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


