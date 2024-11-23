#include <stdio.h>
#include <stdint.h>
#define NUM_ROUNDS 16
void DES_Encryption(uint64_t plaintext, uint64_t key, uint64_t *ciphertext);
void DES_Decryption(uint64_t ciphertext, uint64_t key, uint64_t *plaintext);
void InitialPermutation(uint64_t input, uint64_t *output);
void FinalPermutation(uint64_t input, uint64_t *output);
void FeistelFunction(uint64_t halfBlock, uint64_t subkey, uint64_t *output);
void KeySchedule(uint64_t key, uint64_t subkeys[NUM_ROUNDS]);
int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;  
    uint64_t key = 0x133457799BBCDFF1;   
    uint64_t ciphertext;
    DES_Encryption(plaintext, key, &ciphertext);
    printf("Encrypted ciphertext: %lx\n", ciphertext);
    uint64_t decryptedText;
    DES_Decryption(ciphertext, key, &decryptedText);
    printf("Decrypted plaintext: %lx\n", decryptedText);
    return 0;
}
void DES_Encryption(uint64_t plaintext, uint64_t key, uint64_t *ciphertext) {
    uint64_t L, R, temp, subkeys[NUM_ROUNDS];
    InitialPermutation(plaintext, &temp);
    L = temp >> 32;
    R = temp & 0xFFFFFFFF;
    KeySchedule(key, subkeys);
    for (int round = 0; round < NUM_ROUNDS; round++) {
        FeistelFunction(R, subkeys[round], &temp);
        L ^= temp;
        if (round != NUM_ROUNDS - 1) {
			            uint64_t tempSwap = L;
            L = R;
            R = tempSwap;
        }
    }
    FinalPermutation((L << 32) | R, ciphertext);
}
void DES_Decryption(uint64_t ciphertext, uint64_t key, uint64_t *plaintext) {
    uint64_t L, R, temp, subkeys[NUM_ROUNDS];
    InitialPermutation(ciphertext, &temp);
    L = temp >> 32;
    R = temp & 0xFFFFFFFF;
    KeySchedule(key, subkeys);
    for (int round = NUM_ROUNDS - 1; round >= 0; round--) {
        FeistelFunction(R, subkeys[round], &temp);
        L ^= temp;
        if (round != 0) {
            uint64_t tempSwap = L;
            L = R;
            R = tempSwap;
        }
    }
    FinalPermutation((L << 32) | R, plaintext);
}
void InitialPermutation(uint64_t input, uint64_t *output) {
    
    *output = input;
}
void FinalPermutation(uint64_t input, uint64_t *output) {
    *output = input; 
}
void FeistelFunction(uint64_t halfBlock, uint64_t subkey, uint64_t *output) {
    *output = halfBlock ^ subkey;  
}
void KeySchedule(uint64_t key, uint64_t subkeys[NUM_ROUNDS]) {
    for (int i = 0; i < NUM_ROUNDS; i++) {
        subkeys[i] = key ^ i;  
    }
}
