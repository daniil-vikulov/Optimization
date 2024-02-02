#include "Tests.h"

#include "../include/Exp.h"
#include "../include/Logger.h"

using namespace adaai::solution;
using namespace adaai;

template <typename F>
bool areEqualNegative(F a, F b,
                      F epsilon = std::numeric_limits<F>::epsilon() * 600) {
  if (std::isinf(a)) {
    if (std::isinf(b)) {
      return true;
    } else {
      return false;
    }
  }
  F err = std::abs(a - b);
  if (err <= epsilon) {
    return true;
  }

  return false;
}

template <typename F>
bool areEqualPositive(F a, F b,
                      F epsilon = std::numeric_limits<F>::epsilon() * 600) {
  if (std::isinf(a)) {
    if (std::isinf(b)) {
      return true;
    } else {
      return false;
    }
  }
  F err = std::abs(a / b - 1.0);
  if (err <= epsilon) {
    return true;
  }

  return false;
}

template <typename F> void testExponent(F x) {
  F result = exponent(x);
  F expected = std::exp(x);
  if (std::isnan(result)) {
    if (!std::isnan(expected)) {
      logF("Test failed:", result, "is not equal to", expected);
    } else {
      logI("Test passed: all is nan");
    }
    return;
  }
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
  testExponent<float>(-15.32f);
  testExponent<float>(-std::numeric_limits<float>::infinity());
  testExponent<float>(std::numeric_limits<float>::infinity());
  testExponent<float>(std::numeric_limits<float>::max());
  testExponent<float>(std::numeric_limits<float>::lowest());

  logI("Float mode is tested!!!");
}

void tests::testDouble() {
  logI("Testing exponent in double mode...");

  testExponent<double>(0);
  testExponent<double>(1);
  testExponent<double>(-1);
  testExponent<double>(1.99999);
  testExponent<double>(-0.456);
  testExponent<double>(10.67);
  testExponent<double>(-15.32);
  testExponent<double>(-std::numeric_limits<double>::infinity());
  testExponent<double>(std::numeric_limits<double>::infinity());
  testExponent<double>(std::numeric_limits<double>::max());
  testExponent<double>(std::numeric_limits<double>::lowest());

  logI("Double mode is tested!!!");
}

void tests::testLongDouble() {
  logI("Testing exponent in long double mode...");

  testExponent<long double>(0L);
  testExponent<long double>(1L);
  testExponent<long double>(-1L);
  testExponent<long double>(1.99999L);
  testExponent<long double>(-0.456L);
  testExponent<long double>(10.67L);
  testExponent<long double>(-15.32L);
  testExponent<long double>(-std::numeric_limits<long double>::infinity());
  testExponent<long double>(std::numeric_limits<long double>::infinity());
  testExponent<long double>(std::numeric_limits<long double>::max());
  testExponent<long double>(std::numeric_limits<long double>::lowest());

  logI("Long double mode is tested!!!");
}
