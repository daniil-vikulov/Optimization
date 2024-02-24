#ifndef PADE_TESTS_H
#define PADE_TESTS_H

namespace adaai::tests::inner {
    ///@brief internal Pade-based exponent testing function in float mode
    void testFloatPade();

    ///@brief internal Pade-based exponent testing function in double mode
    void testDoublePade();

    ///@brief internal Pade-based exponent testing function in long double mode
    void testLongDoublePade();
}

#endif