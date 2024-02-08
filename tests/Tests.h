#pragma once

#include "Logger.h"

namespace adaai::tests {
    void checkGmpLib();

    //@brief test exponent function in float mode
    void testFloat();

    ///@brief test exponent function in double mode
    void testDouble();

    ///@brief test exponent function in long double mode
    void testLongDouble();
}
