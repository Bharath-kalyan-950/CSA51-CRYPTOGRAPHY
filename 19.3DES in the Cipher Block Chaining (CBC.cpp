#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK_SIZE 8
void xorBlocks(unsigned char *a, unsigned char *b, unsigned char *result, int len) {
    for (int i = 0; i < len; i++) result[i] = a[i] ^ b[i];
}
void desEncrypt(unsigned char *input, unsigned char *key, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) output[i] = input[i] ^ key[i]; 
}
void tripleDesEncrypt(unsigned char *input, unsigned char *key1, unsigned char *key2, unsigned char *key3, unsigned char *output) {
    unsigned char temp1[BLOCK_SIZE], temp2[BLOCK_SIZE];
    desEncrypt(input, key1, temp1);  
    desEncrypt(temp1, key2, temp2); 
    desEncrypt(temp2, key3, output);
}
void cbcEncrypt(unsigned char *plaintext, int plaintextLen, unsigned char *key1, unsigned char *key2, unsigned char *key3, unsigned char *iv, unsigned char *ciphertext) {
    unsigned char block[BLOCK_SIZE], prevCipherBlock[BLOCK_SIZE];
    memcpy(prevCipherBlock, iv, BLOCK_SIZE);
    for (int i = 0; i < plaintextLen; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xorBlocks(block, prevCipherBlock, block, BLOCK_SIZE);
        tripleDesEncrypt(block, key1, key2, key3, ciphertext + i);
        memcpy(prevCipherBlock, ciphertext + i, BLOCK_SIZE);
    }
}
int main() {
    unsigned char plaintext[] = "This is a test message for CBC encryption!";
    unsigned char key1[BLOCK_SIZE] = "key12345";
    unsigned char key2[BLOCK_SIZE] = "key54321";
    unsigned char key3[BLOCK_SIZE] = "key99999";
    unsigned char iv[BLOCK_SIZE] = "iv123456";
    unsigned char ciphertext[sizeof(plaintext)];
    int plaintextLen = ((strlen((char *)plaintext) + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    unsigned char paddedPlaintext[plaintextLen];
    memcpy(paddedPlaintext, plaintext, strlen((char *)plaintext));
    for (int i = strlen((char *)plaintext); i < plaintextLen; i++) paddedPlaintext[i] = 0;
    cbcEncrypt(paddedPlaintext, plaintextLen, key1, key2, key3, iv, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintextLen; i++) printf("%02x ", ciphertext[i]);
    printf("\n");
    return 0;
}
