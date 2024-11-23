#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define q 23  
#define p 100  
#define g 5    
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}
void DSA_Signature(int m, int x, int *r, int *s) {
    srand(time(NULL));
    int k = rand() % (q - 1) + 1;  
    *r = mod_exp(g, k, p) % q;  
    int k_inv = mod_exp(k, q - 2, q);  
    *s = (k_inv * ((m + x * *r) % q)) % q;  
}
int RSA_Signature(int m, int d, int n) {
    return mod_exp(m, d, n);  
}
int main() {
    int x = 15;  
    int m = 10; 
    int r1, s1, r2, s2;
    DSA_Signature(m, x, &r1, &s1);  
    DSA_Signature(m, x, &r2, &s2);  
    printf("DSA Signatures for the same message:\n");
    printf("Signature 1: (r1: %d, s1: %d)\n", r1, s1);
    printf("Signature 2: (r2: %d, s2: %d)\n", r2, s2);
    int n = 77;  
    int d = 3;   
    int rsa_signature = RSA_Signature(m, d, n);
    printf("\nRSA Signature for the same message: %d\n", rsa_signature);
    return 0;
}
