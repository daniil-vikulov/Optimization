#ifndef TESTS_H
#define TESTS_H

#include "utils/Logger.h"

namespace adaai::tests {

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
