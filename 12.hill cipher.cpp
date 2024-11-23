#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MATRIX_SIZE 2
#define MOD 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}
void matrixMultiply(int mat1[MATRIX_SIZE][MATRIX_SIZE], int vec[MATRIX_SIZE], int res[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        res[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            res[i] += mat1[i][j] * vec[j];
        }
        res[i] %= MOD;
    }
}
void prepareMessage(char *message, char *prepared) {
    int len = 0;
    for (int i = 0; message[i]; i++) {
        if (isalpha(message[i])) {
            prepared[len++] = toupper(message[i]);
        }
    }
    if (len % 2 != 0) {
        prepared[len++] = 'X';
    }
    prepared[len] = '\0';
}
void encryptMessage(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int vec[MATRIX_SIZE], res[MATRIX_SIZE];
    for (int i = 0; plaintext[i] && plaintext[i + 1]; i += 2) {
        vec[0] = plaintext[i] - 'A';
        vec[1] = plaintext[i + 1] - 'A';
        matrixMultiply(key, vec, res);
        ciphertext[i] = res[0] + 'A';
        ciphertext[i + 1] = res[1] + 'A';
    }
}
void decryptMessage(int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (det < 0) det += MOD;
    int detInv = modInverse(det, MOD);
    
    if (detInv == -1) {
        printf("Decryption not possible (no modular inverse).\n");
        return;
    }
    int invKey[MATRIX_SIZE][MATRIX_SIZE];
    invKey[0][0] = (key[1][1] * detInv) % MOD;
    invKey[0][1] = (-key[0][1] * detInv + MOD) % MOD;
    invKey[1][0] = (-key[1][0] * detInv + MOD) % MOD;
    invKey[1][1] = (key[0][0] * detInv) % MOD;
    int vec[MATRIX_SIZE], res[MATRIX_SIZE];
    for (int i = 0; ciphertext[i] && ciphertext[i + 1]; i += 2) {
        vec[0] = ciphertext[i] - 'A';
        vec[1] = ciphertext[i + 1] - 'A';
        matrixMultiply(invKey, vec, res);
        plaintext[i] = res[0] + 'A';
        plaintext[i + 1] = res[1] + 'A';
    }
}
int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    char prepared[100], encrypted[100], decrypted[100];
    int key[MATRIX_SIZE][MATRIX_SIZE] = { {9, 4}, {5, 7} };
    prepareMessage(message, prepared);
    printf("Prepared message: %s\n", prepared);
    memset(encrypted, 0, sizeof(encrypted));
    encryptMessage(key, prepared, encrypted);
    printf("Encrypted message: %s\n", encrypted);
    memset(decrypted, 0, sizeof(decrypted));
    decryptMessage(key, encrypted, decrypted);
    printf("Decrypted message: %s\n", decrypted);
    return 0;
}
