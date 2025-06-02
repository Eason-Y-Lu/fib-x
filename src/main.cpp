#include <iostream>
#include <gmpxx.h>
#include <chrono>
#include <cstdint>

mpz_class fib(uint64_t n) {
    mpz_class a = 0;
    mpz_class b = 1;
    const int highest_bit = 63 - __builtin_clzll(n);

    for (int i = highest_bit; i >= 0; --i) {
        mpz_class two_b_minus_a = (b << 1) - a;
        mpz_class c = a * two_b_minus_a;
        mpz_class d = a * a + b * b;

        if ((n >> i) & 1) {
            a = d;
            b = c + d;
        } else {
            a = c;
            b = d;
        }
    }

    return a;
}

long time_taken(uint64_t n) {
    const auto start = std::chrono::high_resolution_clock::now();
    fib(n);
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    long time = 0;
    int fib_x = 1;
    while (time < 1000000) {
        time = time_taken(fib_x);
        fib_x = fib_x * 2;
        std::cout << "Fibonacci(" << fib_x << ") took " << time << " microseconds." << std::endl;
    }
    std::cout << "Starting Fibonacci check..." << std::endl;
    mpz_class result_wrap = fib(fib_x / 2);
    mpz_t result;
    mpz_init(result);
    mpz_set(result, result_wrap.get_mpz_t());
    mpz_t test_case_1;
    mpz_init(test_case_1);
    mpz_pow_ui(test_case_1, result, 2);
    mpz_t five;
    mpz_init(five);
    mpz_set_ui(five, 5);
    mpz_mul(test_case_1, test_case_1, five);
    mpz_t four;
    mpz_init(four);
    mpz_set_ui(four, 4);
    mpz_add(test_case_1, test_case_1, four);
    mpz_t test_case_2;
    mpz_init(test_case_2);
    mpz_sub(test_case_2, test_case_1, four);
    mpz_sub(test_case_2, test_case_2, four);
    // check if either test_case_1 or test_case_2 is a perfect square
    int is_root_1 = mpz_root(test_case_1, test_case_1, 2);
    int is_root_2 = mpz_root(test_case_2, test_case_2, 2);
    if (is_root_1 == 0 || is_root_2 == 0) {
        std::printf("Fibonacci check passed\n");
    } else {
        std::cout << "Fibonacci check failed" << std::endl;
    }
    return 0;
}
