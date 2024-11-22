#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MOD 26
#define MAX_TEXT 1000
#define TOP_RESULTS 10
void decrypt(int shift, const char *ciphertext, char *plaintext) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - shift + MOD) % MOD) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
double calculateScore(const char *text) {
    double frequencies[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
    double score = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]) - 'A';
            score += frequencies[c];
        }
    }
    return score;
}
void letterFrequencyAttack(const char *ciphertext, int topN) {
    char plaintext[MAX_TEXT];
    double scores[MOD];
    int shifts[MOD];
    for (int shift = 0; shift < MOD; shift++) {
        decrypt(shift, ciphertext, plaintext);
        scores[shift] = calculateScore(plaintext);
        shifts[shift] = shift;
    }
    for (int i = 0; i < MOD - 1; i++) {
        for (int j = i + 1; j < MOD; j++) {
            if (scores[i] < scores[j]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                int tempShift = shifts[i];
                shifts[i] = shifts[j];
                shifts[j] = tempShift;
            }
        }
    }
    for (int i = 0; i < topN && i < MOD; i++) {
        decrypt(shifts[i], ciphertext, plaintext);
        printf("Shift: %d | Plaintext: %s | Score: %.2f\n", shifts[i], plaintext, scores[i]);
    }
}
int main() {
    char ciphertext[MAX_TEXT];
    int topN;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    printf("Enter the number of top results to display: ");
    scanf("%d", &topN);
    letterFrequencyAttack(ciphertext, topN);
    return 0;
}
