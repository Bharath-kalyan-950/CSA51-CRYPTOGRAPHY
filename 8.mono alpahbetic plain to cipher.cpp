#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generate_cipher_sequence(const char *keyword, char cipher[26]) {
    int used[26] = {0}; 
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char letter = toupper(keyword[i]);
        if (!used[letter - 'A']) {
            cipher[index++] = letter;
            used[letter - 'A'] = 1;
        }
    }
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (!used[letter - 'A']) {
            cipher[index++] = letter;
        }
    }
}
void encrypt(const char *plaintext, const char cipher[26], char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char letter = toupper(plaintext[i]);
            ciphertext[i] = isupper(plaintext[i]) ? cipher[letter - 'A'] : tolower(cipher[letter - 'A']);
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}
void decrypt(const char *ciphertext, const char cipher[26], char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = toupper(ciphertext[i]);
            for (int j = 0; j < 26; j++) {
                if (cipher[j] == letter) {
                    plaintext[i] = isupper(ciphertext[i]) ? 'A' + j : tolower('A' + j);
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int main() {
    char keyword[] = "CIPHER";
    char cipher[26];
    char plaintext[256], ciphertext[256], decrypted_text[256];
    generate_cipher_sequence(keyword, cipher);
    printf("Plain alphabet:  ");
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        printf("%c ", letter);
    }
    printf("\nCipher alphabet: ");
    for (int i = 0; i < 26; i++) {
        printf("%c ", cipher[i]);
    }
    printf("\n");
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    encrypt(plaintext, cipher, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, cipher, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text);
    return 0;
}
