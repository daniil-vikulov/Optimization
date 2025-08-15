#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

namespace adaai::tests {
template <typename F> F getMultiplier();

template <> float getMultiplier<float>() {
  static constexpr auto value = static_cast<float>(5);

  return value;
};

template <> double getMultiplier<double>() {
  static constexpr auto value = static_cast<double>(500);

  return value;
};

template <> long double getMultiplier<long double>() {
  static constexpr auto value = static_cast<long double>(5000);

  return value;
};

template <typename F>
bool areEqualNegative(F a, F b,
                      F epsilon = std::numeric_limits<F>::epsilon() *
                                  getMultiplier<F>()) {
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
                      F epsilon = std::numeric_limits<F>::epsilon() *
                                  getMultiplier<F>()) {
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
} // namespace adaai::tests

#endif
