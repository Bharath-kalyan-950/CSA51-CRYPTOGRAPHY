#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
void apply_padding(unsigned char *data, int *data_len, int block_size) {
    int pad_len = block_size - (*data_len % block_size);
    data[*data_len] = 0x80; 
    (*data_len)++;
    for (int i = *data_len; i < *data_len + pad_len - 1; i++) {
        data[i] = 0x00; 
    }
    *data_len += pad_len - 1;
}
void ecb_encrypt(unsigned char *plaintext, int len, unsigned char *key, unsigned char *ciphertext) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);

    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &enc_key);
    }
}
void cbc_encrypt(unsigned char *plaintext, int len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    unsigned char previous_block[AES_BLOCK_SIZE];
    memcpy(previous_block, iv, AES_BLOCK_SIZE);
    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[i + j] ^= previous_block[j]; 
        }
        AES_encrypt(plaintext + i, ciphertext + i, &enc_key);
        memcpy(previous_block, ciphertext + i, AES_BLOCK_SIZE); 
    }
}
void cfb_encrypt(unsigned char *plaintext, int len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    unsigned char previous_block[AES_BLOCK_SIZE];
    memcpy(previous_block, iv, AES_BLOCK_SIZE);
    for (int i = 0; i < len; i++) {
        AES_encrypt(previous_block, previous_block, &enc_key); // Encrypt previous block
        ciphertext[i] = plaintext[i] ^ previous_block[0]; // XOR with first byte of encrypted block
        memcpy(previous_block, previous_block + 1, AES_BLOCK_SIZE - 1); // Shift previous block
        previous_block[AES_BLOCK_SIZE - 1] = ciphertext[i]; // Set last byte of previous block
    }
}
int main() {
    unsigned char key[16] = "0123456789abcdef"; // 128-bit key
    unsigned char iv[AES_BLOCK_SIZE] = "abcdef9876543210"; // 128-bit IV
    unsigned char plaintext[] = "Hello, this is a test message!";
    int len = strlen((char *)plaintext);
    if (len % AES_BLOCK_SIZE != 0) {
        apply_padding(plaintext, &len, AES_BLOCK_SIZE);
    }
    unsigned char ciphertext[256];
    unsigned char decryptedtext[256];
    ecb_encrypt(plaintext, len, key, ciphertext);
    printf("ECB Encrypted: ");
    for (int i = 0; i < len; i++) printf("%02x", ciphertext[i]);
    printf("\n");
    cbc_encrypt(plaintext, len, key, iv, ciphertext);
    printf("CBC Encrypted: ");
    for (int i = 0; i < len; i++) printf("%02x", ciphertext[i]);
    printf("\n");
    cfb_encrypt(plaintext, len, key, iv, ciphertext);
    printf("CFB Encrypted: ");
    for (int i = 0; i < len; i++) printf("%02x", ciphertext[i]);
    printf("\n");
    return 0;
}
