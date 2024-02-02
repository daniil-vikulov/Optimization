#include "tests/Tests.h"
#include "include/Exp.h"
#include <iostream>
#include <iomanip>


int main() {
    // tests::testFloat();
    tests::testDouble();
    // tests::testLongDouble();

    std::cout << std::numeric_limits<float>::epsilon() << "\n";
        std::cout << std::numeric_limits<double>::epsilon() << "\n";
    // float a = -3.7;

    // std::cout << std::setprecision(20) << exponent(a);

    // return 0;
}
