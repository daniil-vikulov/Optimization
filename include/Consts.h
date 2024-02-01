#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <cmath>
#include <cfloat>


template<typename F>
constexpr inline F Ln2;

template<>
constexpr inline float Ln2<float> = 1.f / M_LOG2E;

template<>
constexpr inline float Ln2<double> = 1 / M_LOG2E;

template<>
constexpr inline float Ln2<long double> = 1.L / M_LOG2E;



template<typename F>
constexpr inline F Sqrt2;

template<>
constexpr inline float Sqrt2<float> = 1.f * M_SQRT2;

template<>
constexpr inline double Sqrt2<double> = M_SQRT2;

template<>
constexpr inline long double Sqrt2<long double> = 1.L * M_SQRT2;



template<typename F>
constexpr inline F Eps;

template<>
constexpr inline float Eps<float> = FLT_EPSILON;

template<>
constexpr inline double Eps<double> = DBL_EPSILON;

template<>
constexpr inline long double Eps<long double> = LDBL_EPSILON;

#endif