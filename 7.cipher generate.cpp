#include <stdio.h>
#include <string.h>
#include <ctype.h>
void frequency_analysis(const char *ciphertext, int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= '!' && ciphertext[i] <= '~') { 
            freq[ciphertext[i] - '!']++;
        }
    }
}
void decrypt(const char *ciphertext, const char key[94]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= '!' && ciphertext[i] <= '~') {
            putchar(key[ciphertext[i] - '!']);
        } else {
            putchar(ciphertext[i]); 
        }
    }
    printf("\n");
}
int main() {
    const char ciphertext[] =
        "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
        "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[94] = {0}; 
    char key[94];       
    for (int i = 0; i < 94; i++) {
        key[i] = i + '!';
    }
    frequency_analysis(ciphertext, freq);
    printf("Character frequencies:\n");
    for (int i = 0; i < 94; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i + '!', freq[i]);
        }
    }
    key['‡' - '!'] = 'e'; 
    key['*' - '!'] = 't'; 
    key[';' - '!'] = 'h'; 
    printf("\nDecrypted text:\n");
    decrypt(ciphertext, key);
    return 0;
}
