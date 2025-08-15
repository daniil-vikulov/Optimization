#include "Tests.h"

#include "Exp.h"
#include "Functions.h"

using namespace adaai::solution;
using namespace adaai;

template <typename F> void testExponent(F x) {
  F result = exponent(x);
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

void tests::testFloat() {
  logI("Testing exponent in float mode...");

  const int count = 100000000;
  const float lower_limit = -2147483649.5f;
  const float upper_limit = 2147483648.5f;

  srand(static_cast<unsigned int>(time(nullptr)));

  for (int i = 0; i < count; ++i) {
    float random_value =
        (static_cast<float>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
        lower_limit;
    testExponent<float>(random_value);
  }

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

  const int count = 50000000;
  const double lower_limit = -2147483649.5;
  const double upper_limit = 2147483649.5;

  srand(static_cast<unsigned int>(time(nullptr)));

  for (int i = 0; i < count; ++i) {
    double random_value =
        (static_cast<double>(rand()) / RAND_MAX) * (upper_limit - lower_limit) +
        lower_limit;
    testExponent<double>(random_value);
  }

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

  const int count = 10000000;
  const long double lower_limit = -2147483649.5l;
  const long double upper_limit = 2147483649.5l;

  srand(static_cast<unsigned int>(time(nullptr)));

  for (int i = 0; i < count; ++i) {
    long double random_value = (static_cast<long double>(rand()) / RAND_MAX) *
                                   (upper_limit - lower_limit) +
                               lower_limit;
    testExponent<long double>(random_value);
  }

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
