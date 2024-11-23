#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 16  
#define CONST_128BIT 0x87 
void left_shift(uint8_t *block, uint8_t *output, size_t size) {
    uint8_t carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        uint8_t next_carry = (block[i] & 0x80) ? 1 : 0;  // Check MSB
        output[i] = (block[i] << 1) | carry;
        carry = next_carry;
    }
}
void generate_subkeys(uint8_t *key, size_t block_size, uint8_t *subkey1, uint8_t *subkey2) {
    uint8_t zero_block[BLOCK_SIZE] = {0};  
    uint8_t l[BLOCK_SIZE] = {0};         
    for (int i = 0; i < block_size; i++) {
        l[i] = key[i];  
    }
    left_shift(l, subkey1, block_size);
    if (l[0] & 0x80) {  
        subkey1[block_size - 1] ^= CONST_128BIT;  
    }
    left_shift(subkey1, subkey2, block_size);
    if (subkey1[0] & 0x80) {  
        subkey2[block_size - 1] ^= CONST_128BIT;  
    }
}
int main() {
    uint8_t key[BLOCK_SIZE] = {
        0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0xCF, 0x89, 0x92, 0x34, 0xDC, 0xFE
    };  
    uint8_t subkey1[BLOCK_SIZE] = {0};
    uint8_t subkey2[BLOCK_SIZE] = {0};
    generate_subkeys(key, BLOCK_SIZE, subkey1, subkey2);
    printf("Subkey 1: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", subkey1[i]);
    }
    printf("\n");
    printf("Subkey 2: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", subkey2[i]);
    }
    printf("\n");
    return 0;
}
