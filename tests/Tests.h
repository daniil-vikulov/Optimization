#ifndef TESTS_H
#define TESTS_H

#include "Logger.h"

namespace adaai::tests {
    ///@brief checks whether GSL library has been linked correctly
    void checkGslLib();


    ///@brief testing of Pade-based exponent calculation for float, double and long double
    void testPade();

    ///@brief testing of Taylor-based exponent calculation for float, double and long double
    void testTaylor();


    //@brief internal Taylor-based exponent testing function in float mode
    void testFloatTaylor();

    ///@brief internal Taylor-based exponent testing function in double mode
    void testDoubleTaylor();

    ///@brief internal Taylor-based exponent testing function in long double mode
    void testLongDoubleTaylor();


    //@brief internal Pade-based exponent testing function in float mode
    void testFloatPade();

    ///@brief internal Pade-based exponent testing function in double mode
    void testDoublePade();

    ///@brief internal Pade-based exponent testing function in long double mode
    void testLongDoublePade();
}

#endif