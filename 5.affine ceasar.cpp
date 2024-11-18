#include <stdio.h>
#include <string.h>

// Function to calculate GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular multiplicative inverse of a modulo 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Encryption function
void encryptAffine(char plaintext[], int a, int b) {
    char ciphertext[100];
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((a * (plaintext[i] - 'A') + b) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((a * (plaintext[i] - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("Encrypted Text: %s\n", ciphertext);
}

// Decryption function
void decryptAffine(char ciphertext[], int a, int b) {
    char plaintext[100];
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Multiplicative inverse of a does not exist, decryption not possible.\n");
        return;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'A') - b + 26)) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'a') - b + 26)) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
    printf("Decrypted Text: %s\n", plaintext);
}

int main() {
    char text[100];
    int a, b, choice;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter key a (must be coprime to 26): ");
    scanf("%d", &a);
    printf("Enter key b: ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("Key a is not valid. It must be coprime to 26.\n");
        return 1;
    }

    printf("Choose an option:\n1. Encrypt\n2. Decrypt\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encryptAffine(text, a, b);
    } else if (choice == 2) {
        decryptAffine(text, a, b);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

