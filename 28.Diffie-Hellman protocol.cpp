#include <stdio.h>
#include <math.h>
long powerMod(long base, long exp, long q) {
    long result = 1;
    base = base % q;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % q;
        }
        exp = exp >> 1;
        base = (base * base) % q;
    }
    return result;
}
int main() {
    long q = 23;  
    long a = 5; 
    long x_A = 6;
    long A = powerMod(a, x_A, q);  
    long x_B = 15;
    long B = powerMod(a, x_B, q);  
    long K_A = powerMod(B, x_A, q);  
    long K_B = powerMod(A, x_B, q);  
    printf("Alice's public value: %ld\n", A);
    printf("Bob's public value: %ld\n", B);
    printf("Shared secret key (Alice): %ld\n", K_A);
    printf("Shared secret key (Bob): %ld\n", K_B);
    return 0;
}
