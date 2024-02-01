#pragma once

#include <cmath>


template<typename F>
constexpr F Ln2;

template<>
constexpr float Ln2<float> = M_LN2f;

template<>
constexpr float Ln2<double> = M_LN2;

template<>
constexpr float Ln2<long double> = M_LN2l;



template<typename F>
constexpr F Sqrt2;

template<>
constexpr float Sqrt2<float> = M_SQRT2f;

template<>
constexpr float Sqrt2<double> = M_SQRT2;

template<>
constexpr float Sqrt2<long double> = M_SQRT2l;



template<typename F>
constexpr F Eps = std::numeric_limits<F>::epsilon(); //TODO нафиг
