#include <stdio.h>
#include <string.h>
#define KEY_SIZE 56
#define SUBKEY_SIZE 48
#define ROUNDS 16
int pc1[KEY_SIZE] = { /* Populate PC-1 table */ };
int pc2[SUBKEY_SIZE] = { /* Populate PC-2 table */ };
int shifts[ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
void generateKeys(char *key, char keys[ROUNDS][SUBKEY_SIZE]) {
    char permuted_key[KEY_SIZE];
    char c[ROUNDS + 1][28], d[ROUNDS + 1][28];
    char cd[KEY_SIZE];
    for (int i = 0; i < KEY_SIZE; i++) permuted_key[i] = key[pc1[i] - 1];
    for (int i = 0; i < 28; i++) {
        c[0][i] = permuted_key[i];
        d[0][i] = permuted_key[i + 28];
    }
    for (int i = 1; i <= ROUNDS; i++) {
        int shift = shifts[i - 1];
        for (int j = 0; j < 28; j++) {
            c[i][j] = c[i - 1][(j + shift) % 28];
            d[i][j] = d[i - 1][(j + shift) % 28];
        }
        for (int j = 0; j < 28; j++) cd[j] = c[i][j];
        for (int j = 0; j < 28; j++) cd[j + 28] = d[i][j];
        for (int j = 0; j < SUBKEY_SIZE; j++) keys[i - 1][j] = cd[pc2[j] - 1];
    }
}
void printKeys(char keys[ROUNDS][SUBKEY_SIZE]) {
    for (int i = 0; i < ROUNDS; i++) {
        printf("Subkey %d: ", i + 1);
        for (int j = 0; j < SUBKEY_SIZE; j++) printf("%d", keys[i][j]);
        printf("\n");
    }
}
int main() {
    char key[64] = "1010101010111011000010010001100000100111001101101100110011011101";
    char keys[ROUNDS][SUBKEY_SIZE];
    generateKeys(key, keys);
    printKeys(keys);
    return 0;
}
