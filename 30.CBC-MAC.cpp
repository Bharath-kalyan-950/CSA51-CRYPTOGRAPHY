#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 16 
void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *result, size_t size) {
    for (size_t i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void encrypt_block(uint8_t *key, uint8_t *input, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; 
    }
}
void cbc_mac(uint8_t *key, uint8_t *message, size_t num_blocks, uint8_t *mac) {
    uint8_t temp[BLOCK_SIZE] = {0}; 
    for (size_t i = 0; i < num_blocks; i++) {
        xor_blocks(temp, &message[i * BLOCK_SIZE], temp, BLOCK_SIZE);
        encrypt_block(key, temp, temp);
    }
    memcpy(mac, temp, BLOCK_SIZE);
}
int main() {
    uint8_t key[BLOCK_SIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10
    }; 
    uint8_t message[BLOCK_SIZE] = {
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20
    }; 
    uint8_t mac[BLOCK_SIZE];
    cbc_mac(key, message, 1, mac);
    printf("MAC of single block message X: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac[i]);
    }
    printf("\n");
    uint8_t forged_message[2 * BLOCK_SIZE];
    memcpy(forged_message, message, BLOCK_SIZE);  
    xor_blocks(message, mac, &forged_message[BLOCK_SIZE], BLOCK_SIZE); 
    uint8_t forged_mac[BLOCK_SIZE];
    cbc_mac(key, forged_message, 2, forged_mac);
    printf("MAC of forged two-block message X || (X ? T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", forged_mac[i]);
    }
    printf("\n");
    if (memcmp(mac, forged_mac, BLOCK_SIZE) == 0) {
        printf("Adversary successfully forged the MAC for the two-block message!\n");
    } else {
        printf("MAC forgery failed.\n");
    }
    return 0;
}
