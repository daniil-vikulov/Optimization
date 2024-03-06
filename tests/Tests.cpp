#include "Tests.h"

#include <sstream>

#include "Exp.h"
#include "Functions.h"

using namespace adaai;
using namespace adaai::solution;

void tests::testFFT() {
    logI("Testing FFT...");
    //TODO
    logI("FFT tested!!!");
}

void tests::testFloatFFT() {
    //TODO
}

void tests::testDoubleFFT() {
    //TODO
}

void tests::testLongDoubleFFT() {
    //TODO
}

void tests::testFftCalculation() {
    std::vector<double> coefficients = {4.0, 3.0, 2.0, 1.0};

    auto res = calculateSum(coefficients);

    logI(res[0], res[1]);
}
