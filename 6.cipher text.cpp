#include <stdio.h>
#include <ctype.h>
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}
void decrypt(char ciphertext[], int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid key, no modular inverse exists for a.\n");
        return;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            int y = ciphertext[i] - offset; 
            int x = (a_inv * (y - b + 26)) % 26; 
            printf("%c", x + offset);
        } else {
            printf("%c", ciphertext[i]); 
        }
    }
    printf("\n");
}
int main() {
    char ciphertext[] = "BLAH..."; 
    int a = 15; 
    int b = 23; 

    printf("Decrypted text: ");
    decrypt(ciphertext, a, b);

    return 0;
}
