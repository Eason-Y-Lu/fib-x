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
        fib_x = fib_x*2;
        std::cout << "Fibonacci(" << fib_x << ") took " << time << " microseconds." << std::endl;
    }
    mpz_class result = fib(fib_x / 2);

}
