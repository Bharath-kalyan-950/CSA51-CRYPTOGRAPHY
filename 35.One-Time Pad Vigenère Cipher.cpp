#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ALPHABET_SIZE 26
char encrypt_char(char plaintext, int key) {
    if (plaintext >= 'A' && plaintext <= 'Z') {
        return 'A' + (plaintext - 'A' + key) % ALPHABET_SIZE;
    } else if (plaintext >= 'a' && plaintext <= 'z') {
        return 'a' + (plaintext - 'a' + key) % ALPHABET_SIZE;
    }
    return plaintext;  
}
void generate_key(int *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE; 
    }
}
int main() {
    char plaintext[256];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    size_t length = strlen(plaintext);
    int key[length];
    srand(time(NULL));
    generate_key(key, length);
    char ciphertext[length + 1];
    for (size_t i = 0; i < length; i++) {
        ciphertext[i] = encrypt_char(plaintext[i], key[i]);
    }
    ciphertext[length] = '\0'; 
    printf("Key: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\nCiphertext: %s\n", ciphertext);
    return 0;
}
