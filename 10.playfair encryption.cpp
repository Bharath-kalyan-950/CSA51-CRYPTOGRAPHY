#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void preprocessText(char text[]) {
    int i, j = 0;
    char result[256];
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            result[j++] = toupper(text[i] == 'J' ? 'I' : text[i]);
        }
    }
    result[j] = '\0';
    j = 0;
    for (i = 0; result[i] != '\0'; i++) {
        text[j++] = result[i];
        if (result[i] == result[i + 1]) {
            text[j++] = 'X';
        }
    }
    if (j % 2 != 0) {
        text[j++] = 'X';
    }
    text[j] = '\0';
}
void findPosition(char c, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char a, char b, char *x, char *y) {
    int r1, c1, r2, c2;
    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);
    if (r1 == r2) {
        *x = playfairMatrix[r1][(c1 + 1) % SIZE];
        *y = playfairMatrix[r2][(c2 + 1) % SIZE];
    } else if (c1 == c2) {
        *x = playfairMatrix[(r1 + 1) % SIZE][c1];
        *y = playfairMatrix[(r2 + 1) % SIZE][c2];
    } else {
        *x = playfairMatrix[r1][c2];
        *y = playfairMatrix[r2][c1];
    }
}
void encryptPlayfair(char plaintext[], char ciphertext[]) {
    int i, k = 0;
    preprocessText(plaintext);
    for (i = 0; i < strlen(plaintext); i += 2) {
        char x, y;
        encryptPair(plaintext[i], plaintext[i + 1], &x, &y);
        ciphertext[k++] = x;
        ciphertext[k++] = y;
    }
    ciphertext[k] = '\0';
}
int main() {
    char plaintext[256] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[256];
    encryptPlayfair(plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
