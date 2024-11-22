#include <stdio.h>
#include <string.h>
#define ROUNDS 16
#define KEY_SIZE 48
#define BLOCK_SIZE 64
int initial_permutation[BLOCK_SIZE] = { };
int final_permutation[BLOCK_SIZE] = {  };
int pc1[56] = { };
int pc2[KEY_SIZE] = {  };
int shifts[ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
int sboxes[8][4][16] = {  };
void generateKeys(char *key, char keys[ROUNDS][KEY_SIZE]) {
    char permuted_key[56];
    char c[ROUNDS + 1][28], d[ROUNDS + 1][28];
    char cd[56];

    for (int i = 0; i < 56; i++) permuted_key[i] = key[pc1[i] - 1];
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
        for (int j = 0; j < KEY_SIZE; j++) keys[i - 1][j] = cd[pc2[j] - 1];
    }
}
void desDecrypt(char *ciphertext, char *key, char *plaintext) {
    char keys[ROUNDS][KEY_SIZE];
    char permuted_text[BLOCK_SIZE], l[ROUNDS + 1][32], r[ROUNDS + 1][32];
    char combined[BLOCK_SIZE], temp[32];

    generateKeys(key, keys);
    for (int i = 0; i < BLOCK_SIZE; i++) permuted_text[i] = ciphertext[initial_permutation[i] - 1];
    for (int i = 0; i < 32; i++) l[0][i] = permuted_text[i];
    for (int i = 0; i < 32; i++) r[0][i] = permuted_text[i + 32];

    for (int round = 1; round <= ROUNDS; round++) {
        for (int i = 0; i < 32; i++) l[round][i] = r[round - 1][i];
        for (int i = 0; i < 32; i++) r[round][i] = l[round - 1][i] ^ temp[i];
    }
    for (int i = 0; i < 32; i++) combined[i] = r[ROUNDS][i];
    for (int i = 0; i < 32; i++) combined[i + 32] = l[ROUNDS][i];
    for (int i = 0; i < BLOCK_SIZE; i++) plaintext[i] = combined[final_permutation[i] - 1];
}	
int main() {
    char key[64] = "1010101010111011000010010001100000100111001101101100110011011101";
    char ciphertext[64] = "1100110000000000110011001111111101010101010101011111000010101010";
    char plaintext[64];

    desDecrypt(ciphertext, key, plaintext);

    printf("Decrypted plaintext: %s\n", plaintext);
    return 0;
}
