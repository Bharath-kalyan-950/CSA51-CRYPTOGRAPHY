#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long gcd(long a, long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
long modInverse(long a, long m) {
    long m0 = m, t, q;
    long x0 = 0, x1 = 1;   
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;   
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;   
    return x1;
}
int main() {
    long p = 61, q = 53; 
    long n = p * q;
    long phi = (p - 1) * (q - 1);
    long e = 17; 
    long d = modInverse(e, phi);
    
    printf("Public key: (n = %ld, e = %ld)\n", n, e);
    printf("Private key: (n = %ld, d = %ld)\n", n, d);   
    return 0;
}
