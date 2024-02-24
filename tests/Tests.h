#ifndef TESTS_H
#define TESTS_H

namespace adaai::tests {
    ///@brief checks whether GSL library has been linked correctly
    void testGslLib();

    ///@brief testing of Taylor-based exponent calculation for float, double and long double
    void testTaylor();

    ///@brief testing of Pade-based exponent calculation for float, double and long double
    void testPade();
}

#endif