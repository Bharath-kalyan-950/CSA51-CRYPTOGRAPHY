#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char key[], char text[], char extendedKey[]) {
    int textLength = strlen(text);
    int keyLength = strlen(key);
    for (int i = 0; i < textLength; i++) {
        extendedKey[i] = key[i % keyLength];
    }
    extendedKey[textLength] = '\0';
}

void polyalphabeticCipher(char text[], char key[], int mode) {
    char result[100];
    char extendedKey[100];
    generateKey(key, text, extendedKey);
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int shift = (mode == 1) 
                        ? (toupper(extendedKey[i]) - 'A') 
                        : (26 - (toupper(extendedKey[i]) - 'A'));
            if (isupper(text[i])) {
                result[i] = ((text[i] - 'A' + shift) % 26) + 'A';
            } else if (islower(text[i])) {
                result[i] = ((text[i] - 'a' + shift) % 26) + 'a';
            }
        } else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
    printf("%s\n", result);
}

int main() {
    char text[100], key[100];
    int choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("Choose an option:\n1. Encrypt\n2. Decrypt\nEnter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Encrypted text: ");
        polyalphabeticCipher(text, key, 1);
    } else if (choice == 2) {
        printf("Decrypted text: ");
        polyalphabeticCipher(text, key, 2);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

