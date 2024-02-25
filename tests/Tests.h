#ifndef TESTS_H
#define TESTS_H

#include "Logger.h"

namespace adaai::tests {
    ///@brief checks whether GMP library has been linked correctly
    void checkGmpLib();

    ///@brief testing of Chebyshev-based exponent calculation for float, double and long double
    void testChebyshev();

    //@brief internal Chebyshev-based exponent testing function in float mode
    void testFloatChebyshev();

    ///@brief internal Chebyshev-based exponent testing function in double mode
    void testDoubleChebyshev();

    ///@brief internal Chebyshev-based exponent testing function in long double mode
    void testLongDoubleChebyshev();

}

#endif
