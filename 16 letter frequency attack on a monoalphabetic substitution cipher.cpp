#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT 1000
#define ALPHABET 26
#define TOP_RESULTS 10
double englishFrequencies[ALPHABET] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};

void calculateFrequencies(const char *text, double *frequencies) {
    int counts[ALPHABET] = {0}, total = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            counts[toupper(text[i]) - 'A']++;
            total++;
        }
    }
    for (int i = 0; i < ALPHABET; i++) {
        frequencies[i] = (counts[i] / (double)total) * 100.0;
    }
}
double calculateScore(const double *frequencies) {
    double score = 0;
    for (int i = 0; i < ALPHABET; i++) {
        score += frequencies[i] * englishFrequencies[i];
    }
    return score;
}
void decryptWithMapping(const char *ciphertext, const char *mapping, char *plaintext) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = mapping[toupper(ciphertext[i]) - 'A'] + (islower(ciphertext[i]) ? 32 : 0);
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void generateMappings(char mappings[ALPHABET][ALPHABET], const double *frequencies) {
    int sortedIndices[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) sortedIndices[i] = i;
    for (int i = 0; i < ALPHABET - 1; i++) {
        for (int j = i + 1; j < ALPHABET; j++) {
            if (frequencies[sortedIndices[i]] < frequencies[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }
    for (int i = 0; i < ALPHABET; i++) {
        for (int j = 0; j < ALPHABET; j++) {
            mappings[i][sortedIndices[j]] = 'A' + j;
        }
    }
}
void letterFrequencyAttack(const char *ciphertext, int topN) {
    double cipherFrequencies[ALPHABET];
    char mappings[ALPHABET][ALPHABET];
    char plaintext[MAX_TEXT];
    calculateFrequencies(ciphertext, cipherFrequencies);
    generateMappings(mappings, cipherFrequencies);
    for (int i = 0; i < topN && i < ALPHABET; i++) {
        decryptWithMapping(ciphertext, mappings[i], plaintext);
        printf("Mapping %d: %s\n", i + 1, plaintext);
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
