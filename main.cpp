#include "tests/Tests.h"

int main() {
    adaai::tests::checkGmpLib();

    adaai::tests::testFloat();
    adaai::tests::testDouble();
    adaai::tests::testLongDouble();
    
    return 0;
}
