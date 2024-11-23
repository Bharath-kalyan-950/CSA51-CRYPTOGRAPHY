#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 8  
void pad_plaintext(uint8_t *plaintext, size_t *length) {
    size_t padding_length = BLOCK_SIZE - (*length % BLOCK_SIZE);
    if (padding_length == 0) padding_length = BLOCK_SIZE;
    plaintext[*length] = 0x80; 
    for (size_t i = 1; i < padding_length; i++) {
        plaintext[*length + i] = 0x00; 
    }
    *length += padding_length;
}
void ecb_encrypt(uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *ciphertext) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ key[j]; 
        }
    }
}
int main() {
    uint8_t plaintext[64] = "HELLO, THIS IS A TEST MESSAGE.";  
    size_t length = strlen((char *)plaintext);
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};  
    uint8_t ciphertext[64] = {0};
    pad_plaintext(plaintext, &length);
    ecb_encrypt(plaintext, length, key, ciphertext);
    printf("Ciphertext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    return 0;
}
