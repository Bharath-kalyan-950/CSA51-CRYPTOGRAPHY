#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MATRIX_SIZE 2 
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
void matrixMultiply(int mat1[MATRIX_SIZE][MATRIX_SIZE], int mat2[MATRIX_SIZE], int res[MATRIX_SIZE], int mod) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        res[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            res[i] += mat1[i][j] * mat2[j];
        }
        res[i] %= mod;
    }
}
void encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], int plaintext[MATRIX_SIZE], int ciphertext[MATRIX_SIZE]) {
    matrixMultiply(key, plaintext, ciphertext, 26);
}
void decryptUsingKnownPlaintext(int plaintext[MATRIX_SIZE], int ciphertext[MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;
    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        printf("Modular inverse not found. Cannot decrypt.\n");
        return;
    }
    int inverseKey[MATRIX_SIZE][MATRIX_SIZE];
    inverseKey[0][0] = (key[1][1] * detInv) % 26;
    inverseKey[0][1] = (-key[0][1] * detInv + 26) % 26;
    inverseKey[1][0] = (-key[1][0] * detInv + 26) % 26;
    inverseKey[1][1] = (key[0][0] * detInv) % 26;
    int decrypted[MATRIX_SIZE];
    matrixMultiply(inverseKey, ciphertext, decrypted, 26);
    printf("Decrypted text: ");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%c", decrypted[i] + 'A');
    }
    printf("\n");
}
int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = { {3, 3}, {2, 5} };
    int plaintext[MATRIX_SIZE] = { 7, 4 }; 
    int ciphertext[MATRIX_SIZE];
    encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%c", ciphertext[i] + 'A');
    }
    printf("\n");
    decryptUsingKnownPlaintext(plaintext, ciphertext, key);
    return 0;
}
