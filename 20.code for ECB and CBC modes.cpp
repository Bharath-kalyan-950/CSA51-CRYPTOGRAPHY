#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8
void xorBlocks(unsigned char *a, unsigned char *b, unsigned char *result, int len) {
    for (int i = 0; i < len; i++) result[i] = a[i] ^ b[i];
}
void encryptBlock(unsigned char *input, unsigned char *key, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) output[i] = input[i] ^ key[i];
}
void ecbEncrypt(unsigned char *plaintext, int plaintextLen, unsigned char *key, unsigned char *ciphertext) {
    for (int i = 0; i < plaintextLen; i += BLOCK_SIZE) {
        encryptBlock(plaintext + i, key, ciphertext + i);
    }
}
void cbcEncrypt(unsigned char *plaintext, int plaintextLen, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    unsigned char block[BLOCK_SIZE];
    unsigned char prevCipherBlock[BLOCK_SIZE];
    memcpy(prevCipherBlock, iv, BLOCK_SIZE);
    for (int i = 0; i < plaintextLen; i += BLOCK_SIZE) {
        xorBlocks(plaintext + i, prevCipherBlock, block, BLOCK_SIZE);
        encryptBlock(block, key, ciphertext + i);
        memcpy(prevCipherBlock, ciphertext + i, BLOCK_SIZE);
    }
}
void simulateError(unsigned char *data, int position) {
    data[position] ^= 0xFF; 
}
int main() {
    unsigned char plaintext[] = "This is a test for ECB and CBC error propagation!";
    unsigned char key[BLOCK_SIZE] = "key12345";
    unsigned char iv[BLOCK_SIZE] = "iv123456";
    unsigned char ecbCiphertext[sizeof(plaintext)];
    unsigned char cbcCiphertext[sizeof(plaintext)];
    int plaintextLen = ((strlen((char *)plaintext) + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    unsigned char paddedPlaintext[plaintextLen];
    memcpy(paddedPlaintext, plaintext, strlen((char *)plaintext));
    for (int i = strlen((char *)plaintext); i < plaintextLen; i++) paddedPlaintext[i] = 0;
    ecbEncrypt(paddedPlaintext, plaintextLen, key, ecbCiphertext);
    cbcEncrypt(paddedPlaintext, plaintextLen, key, iv, cbcCiphertext);
    simulateError(ecbCiphertext, 8);
    simulateError(cbcCiphertext, 8); 
    printf("ECB Ciphertext (with error): ");
    for (int i = 0; i < plaintextLen; i++) printf("%02x ", ecbCiphertext[i]);
    printf("\n");
    printf("CBC Ciphertext (with error): ");
    for (int i = 0; i < plaintextLen; i++) printf("%02x ", cbcCiphertext[i]);
    printf("\n");
    return 0;
}
