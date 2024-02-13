#ifndef CONSTS_H
#define CONSTS_H

#include "GccConsts.h"
#include <cfloat>
#include <cmath>

namespace adaai::solution {
template <typename F> constexpr inline F Ln2;

template <> constexpr inline float Ln2<float> = 1 / M_LOG2Ef;

template <> constexpr inline double Ln2<double> = 1 / M_LOG2E;

template <> constexpr inline long double Ln2<long double> = 1 / M_LOG2El;

template <typename F> constexpr inline F Sqrt2;

template <> constexpr inline float Sqrt2<float> = M_SQRT2f;

template <> constexpr inline double Sqrt2<double> = M_SQRT2;

template <> constexpr inline long double Sqrt2<long double> = M_SQRT2l;

template <typename F> constexpr inline F Eps;

template <> constexpr inline float Eps<float> = FLT_EPSILON;

template <> constexpr inline double Eps<double> = DBL_EPSILON;

template <> constexpr inline long double Eps<long double> = LDBL_EPSILON;

template <typename F> 
constexpr inline int MKExpTaylorOrder() {
  F curr_eps = Ln2<F> * Sqrt2<F> / 2;
  for(int i = 1; i < 1000; ++i) {
    if(curr_eps < 10.0 * Eps<F>){
      return i-1;
    } 
    curr_eps *= (Ln2<F> * 0.5) / (i+1);
  }
  assert(false); 
}

} // namespace adaai::solution


#endif
