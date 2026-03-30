#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int zeros = 0, ones = 0;
    int total_bits = 100000;

    srand(time(NULL));

    for (int i = 0; i < total_bits; i++) {
        int bit = rand() % 2; 
        
        if (bit == 0) zeros++;
        else ones++;
    }

    printf("--- BIT BIAS TEST ---\n");
    printf("Total bits: %d\n", total_bits);
    printf("Zeros: %d (%.2f%%)\n", zeros, (float)zeros/total_bits * 100);
    printf("Ones:  %d (%.2f%%)\n", ones, (float)ones/total_bits * 100);

    if (abs(zeros - ones) < (total_bits * 0.01)) {
        printf("Result: Good distribution (Fair).\n");
    } else {
        printf("Result: Bias detected!\n");
    }

    return 0;
}