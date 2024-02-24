#ifndef TAYLOR_TESTS_H
#define TAYLOR_TESTS_H

namespace adaai::tests::inner {
    ///@brief internal Taylor-based exponent testing function in float mode
    void testFloatTaylor();

    ///@brief internal Taylor-based exponent testing function in double mode
    void testDoubleTaylor();

    ///@brief internal Taylor-based exponent testing function in long double mode
    void testLongDoubleTaylor();
}

#endif