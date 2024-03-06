#ifndef TESTS_H
#define TESTS_H

#include "utils/Logger.h"

namespace adaai::tests {

    ///@brief testing of FFT exponent calculation for float, double and long double
    void testFFT();

    //@brief internal FFT exponent testing function in float mode
    void testFloatFFT();

    ///@brief internal FFT exponent testing function in double mode
    void testDoubleFFT();

    ///@brief internal FFT exponent testing function in long double mode
    void testLongDoubleFFT();

    void testFftCalculation();
}

#endif
