#include <stdio.h>
#include <ctype.h>
#include <string.h>
void encrypt(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a'; 
            text[i] = (c - offset + k) % 26 + offset;
        }
    }
}
void decrypt(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a'; 
            text[i] = (c - offset - k + 26) % 26 + offset; 
        }
    }
}
int main() {
    char text[100];
    int k, choice;
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    printf("Enter the shift value (k): ");
    scanf("%d", &k);
    if (k < 1 || k > 25) {
        printf("Invalid shift value. It must be between 1 and 25.\n");
        return 1;
    }
    printf("Choose an option:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encrypt(text, k);
        printf("Encrypted text: %s\n", text);
    } else if (choice == 2) {
        decrypt(text, k);
        printf("Decrypted text: %s\n", text);
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}
