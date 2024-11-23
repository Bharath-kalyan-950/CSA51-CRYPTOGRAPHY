#include <stdio.h>
#include <string.h>
int P10(int key) {
    int permuted = 0;
    int P10_table[10] = {2, 4, 1, 6, 3, 9, 5, 8, 7, 10};
    for (int i = 0; i < 10; i++) {
        int bit = (key >> (10 - P10_table[i])) & 1;
        permuted |= (bit << (9 - i));
    }
    return permuted;
}
int P8(int key) {
    int permuted = 0;
    int P8_table[8] = {6, 3, 7, 4, 8, 5, 10, 9};
    for (int i = 0; i < 8; i++) {
        int bit = (key >> (10 - P8_table[i])) & 1;
        permuted |= (bit << (7 - i));
    }
    return permuted;
}
int shift_left(int block, int shifts) {
    return ((block << shifts) | (block >> (5 - shifts))) & 0x1F;
}
int S1(int input) {
    int S1_table[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 1, 2, 3}, {2, 3, 0, 1}};
    int row = ((input >> 3) & 1) | ((input & 1) << 1);
    int col = (input >> 1) & 3;
    return S1_table[row][col];
}
int S2(int input) {
    int S2_table[4][4] = {{0, 1, 2, 3}, {3, 2, 1, 0}, {2, 3, 0, 1}, {1, 0, 3, 2}};
    int row = ((input >> 3) & 1) | ((input & 1) << 1);
    int col = (input >> 1) & 3;
    return S2_table[row][col];
}
int IP(int block) {
    int permuted = 0;
    int IP_table[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    for (int i = 0; i < 8; i++) {
        int bit = (block >> (8 - IP_table[i])) & 1;
        permuted |= (bit << (7 - i));
    }
    return permuted;
}
int IP_1(int block) {
    int permuted = 0;
    int IP_1_table[8] = {4, 1, 3, 5, 7, 2, 8, 6};
    for (int i = 0; i < 8; i++) {
        int bit = (block >> (8 - IP_1_table[i])) & 1;
        permuted |= (bit << (7 - i));
    }
    return permuted;
}
int F(int block, int key) {
    int left = (block >> 4) & 0xF;
    int right = block & 0xF;
    left = S1(left ^ ((key >> 4) & 0xF));
    right = S2(right ^ (key & 0xF));
    return (left << 4) | right;
}
void generate_subkeys(int key, int* K1, int* K2) {
    int key_p10 = P10(key);
    int left = (key_p10 >> 5) & 0x1F;
    int right = key_p10 & 0x1F;
    left = shift_left(left, 1);
    right = shift_left(right, 1);
    *K1 = P8((left << 5) | right);
    left = shift_left(left, 2);
    right = shift_left(right, 2);
    *K2 = P8((left << 5) | right);
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
void CBC_encrypt(int* plaintext, int block_size, int* iv, int key, int* ciphertext) {
    int K1, K2;
    generate_subkeys(key, &K1, &K2);
    int prev_cipher = *iv;
    for (int i = 0; i < block_size; i++) {
        int block = plaintext[i] ^ prev_cipher;
        ciphertext[i] = encrypt(block, K1, K2);
        prev_cipher = ciphertext[i];
    }
}
void CBC_decrypt(int* ciphertext, int block_size, int* iv, int key, int* plaintext) {
    int K1, K2;
    generate_subkeys(key, &K1, &K2);
    int prev_cipher = *iv;
    for (int i = 0; i < block_size; i++) {
        int block = decrypt(ciphertext[i], K1, K2);
        plaintext[i] = block ^ prev_cipher;
        prev_cipher = ciphertext[i];
    }
}
int main() {
    int key = 0x7F;
    int iv = 0xAA;  
    int plaintext[] = {0x01, 0x23}; 
    int ciphertext[2];
    int decrypted_text[2];
    printf("Encrypting...\n");
    CBC_encrypt(plaintext, 2, &iv, key, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < 2; i++) {
        printf("%04X ", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypting...\n");
    CBC_decrypt(ciphertext, 2, &iv, key, decrypted_text);
    printf("Decrypted Text: ");
    for (int i = 0; i < 2; i++) {
        printf("%04X ", decrypted_text[i]);
    }
    printf("\n");
    return 0;
}
