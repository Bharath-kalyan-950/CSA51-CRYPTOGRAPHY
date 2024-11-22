#include <stdio.h>
#include <math.h>
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
void calculateKeys() {
    double totalPermutations = factorial(25);
    double uniqueKeys = pow(2, 50);
    printf("Total possible keys (approx.): 2^%.0f\n", log2(totalPermutations));
    printf("Effectively unique keys (approx.): 2^50\n");
}
int main() {
    calculateKeys();
    return 0;
}
