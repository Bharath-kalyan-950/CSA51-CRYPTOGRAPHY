#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MOD 26
void generateKey(int *key, int length) {
    srand(time(0)); 
    for (int i = 0; i < length; i++) {
        key[i] = rand() % MOD; 
    }
}
void encryptMessage(const char *plaintext, int *key, char *ciphertext) {
    for (int i = 0; plaintext[i]; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - base + key[i]) % MOD) + base;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}
void decryptMessage(const char *ciphertext, int *key, char *plaintext) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key[i] + MOD) % MOD) + base;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int key[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    int length = strlen
    generateKey(key, length);
    printf("Generated key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    encryptMessage(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decryptMessage(ciphertext, key, decrypted);
    printf("Decrypted message: %s\n", decrypted);
    return 0;
}
