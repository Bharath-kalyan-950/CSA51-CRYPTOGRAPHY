#include <stdio.h>
#include <string.h>

// Helper functions for S-DES

int P10(int key);
int P8(int key);
int S1(int input);
int S2(int input);
int IP(int block);
int IP_1(int block);
int F(int block, int key);
int shift_left(int block, int shifts);
int xor(int a, int b);
void generate_subkeys(int key, int* K1, int* K2) {
    int key_p10 = P10(key);
    *K1 = P8(shift_left(key_p10, 1));
    *K2 = P8(shift_left(*K1, 2));
}
int encrypt(int block, int key1, int key2) {
    int ip_block = IP(block);
    int left = (ip_block >> 4) & 0xF;
    int right = ip_block & 0xF;
    int temp = F(left, key1) ^ right;
    right ^= F(temp, key2);
    return IP_1((left << 4) | right);
}
int decrypt(int block, int key1, int key2) {
    int ip_block = IP(block);
    int left = (ip_block >> 4) & 0xF;
    int right = ip_block & 0xF;
    int temp = F(left, key2) ^ right;
    right ^= F(temp, key1);
    return IP_1((left << 4) | right);
}
int xor_blocks(int a, int b) {
    return a ^ b;
}

// Function to generate keystream for CTR mode (fixed block size to 8 bits)
void generate_keystream(int* counter, int key, int* keystream, int block_size) {
    int K1, K2;
    generate_subkeys(key, &K1, &K2);

    for (int i = 0; i < block_size; i++) {
        // Use counter directly for keystream generation
        int block = (*counter + i) & 0xFF;  // Using the counter and increment
        keystream[i] = encrypt(block, K1, K2);
    }
}

// CTR mode encryption
void CTR_encrypt(int* plaintext, int block_size, int* counter, int key, int* ciphertext) {
    int keystream[block_size];
    generate_keystream(counter, key, keystream, block_size);

    for (int i = 0; i < block_size; i++) {
        ciphertext[i] = xor_blocks(plaintext[i], keystream[i]);
    }
}

// CTR mode decryption
void CTR_decrypt(int* ciphertext, int block_size, int* counter, int key, int* plaintext) {
    int keystream[block_size];
    generate_keystream(counter, key, keystream, block_size);

    for (int i = 0; i < block_size; i++) {
        plaintext[i] = xor_blocks(ciphertext[i], keystream[i]);
    }
}

int main() {
    int key = 0x7F; // 0111111101 in binary (S-DES key)
    int counter = 0; // Starting at 0000 0000
    int plaintext[] = {0x01, 0x20, 0x40}; // 0000 0001 0000 0010 0000 0100 in binary (Plaintext)
    int ciphertext[3];
    int decrypted_text[3];

    printf("Encrypting...\n");
    CTR_encrypt(plaintext, 3, &counter, key, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < 3; i++) {
        printf("%04X ", ciphertext[i]);
    }
    printf("\n");

    // Reset counter for decryption
    counter = 0;
    printf("Decrypting...\n");
    CTR_decrypt(ciphertext, 3, &counter, key, decrypted_text);
    printf("Decrypted Text: ");
    for (int i = 0; i < 3; i++) {
        printf("%04X ", decrypted_text[i]);
    }
    printf("\n");

    return 0;
}

