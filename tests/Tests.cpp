#include "Tests.h"

#include <gmp.h>
#include <sstream>

using namespace adaai;

void tests::checkGmpLib() {
    mpz_t op1, op2, result;

    mpz_init(op1);
    mpz_init(op2);
    mpz_init(result);

    mpz_set_ui(op1, 1234); // op1 = 1234
    mpz_set_ui(op2, 5678); // op2 = 5678

    mpz_add(result, op1, op2);

    std::cout << "Result of adding 1234 and 5678 using GMP: ";
    mpz_out_str(stdout, 10, result);
    std::cout << std::endl;

    mpz_clear(op1);
    mpz_clear(op2);
    mpz_clear(result);
}
