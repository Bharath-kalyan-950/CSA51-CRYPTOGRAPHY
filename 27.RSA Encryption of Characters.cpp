#include <stdio.h>
#include <math.h>
long powerMod(long base, long exp, long mod) {
    long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
int main() {
    long n = 3233;  
    long e = 17;    
    char message[] = "HELLO";
    long ciphertext[5];
    printf("Original message: %s\n", message);
    for (int i = 0; i < 5; i++) {
        int m = message[i] - 'A';
        ciphertext[i] = powerMod(m, e, n); 
        printf("Encrypted '%c' -> %ld\n", message[i], ciphertext[i]);
    }
    return 0;
}
