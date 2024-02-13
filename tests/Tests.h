#ifndef TESTS_H
#define TESTS_H

#include "Logger.h"

namespace adaai::tests {
    ///@brief checks whether GMP library has been linked correctly
    void checkGmpLib();

    ///@brief testing of Pade-based exponent calculation for float, double and long double
    void testPade();

    ///@brief testing of Taylor-based exponent calculation for float, double and long double
    void testTaylor();

    //@brief internal testing  exponent function in float mode
    void testFloatTaylor();

    ///@brief test exponent function in double mode
    void testDoubleTaylor();

    ///@brief test exponent function in long double mode
    void testLongDoubleTaylor();

    //@brief internal testing  exponent function in float mode
    void testFloatPade();

    ///@brief test exponent function in double mode
    void testDoublePade();

    ///@brief test exponent function in long double mode
    void testLongDoublePade();
}

#endif