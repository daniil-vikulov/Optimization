#include "tests/Tests.h"
#include "include/Exp.h"
#include <iostream>
#include <iomanip>


int main() {
    tests::testFloat();
    tests::testDouble();
    tests::testLongDouble();

    return 0;
}
