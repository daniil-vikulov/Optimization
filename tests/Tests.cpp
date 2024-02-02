#include "Tests.h"

#include "Exp.h"

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

  testExponent(0.f);
  testExponent(1.f);
  testExponent(-1.f);
  testExponent(1.99999f);
  testExponent(-0.456f);
  testExponent(10.67f);
  testExponent(-15.32f);
  testExponent(-std::numeric_limits<float>::infinity());
  testExponent(std::numeric_limits<float>::infinity());
  testExponent(std::numeric_limits<float>::max());
  testExponent(std::numeric_limits<float>::lowest());

  logI("Float mode is tested!!!");
}

void tests::testDouble() {
  logI("Testing exponent in double mode...");

  testExponent(0.f);
  testExponent(1.f);
  testExponent(-1.f);
  testExponent(1.99999);
  testExponent(-0.456);
  testExponent(10.67);
  testExponent(-15.32);
  testExponent(-std::numeric_limits<double>::infinity());
  testExponent(std::numeric_limits<double>::infinity());
  testExponent(std::numeric_limits<double>::max());
  testExponent(std::numeric_limits<double>::lowest());

  logI("Double mode is tested!!!");
}

void tests::testLongDouble() {
  logI("Testing exponent in long double mode...");

  testExponent(0.l);
  testExponent(1.l);
  testExponent(-1.l);
  testExponent(1.99999l);
  testExponent(-0.456l);
  testExponent(10.67l);
  testExponent(-15.32l);
  testExponent(-std::numeric_limits<long double>::infinity());
  testExponent(std::numeric_limits<long double>::infinity());
  testExponent(std::numeric_limits<long double>::max());
  testExponent(std::numeric_limits<long double>::lowest());

  logI("Long double mode is tested!!!");
}
