#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int alphabet[26] = {0}; 
    int x = 0, y = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = tolower(key[i]);
        if (c == 'j') c = 'i'; 
        if (!alphabet[c - 'a']) {
            matrix[x][y++] = c;
            alphabet[c - 'a'] = 1;
            if (y == SIZE) { y = 0; x++; }
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue; 
        if (!alphabet[c - 'a']) {
            matrix[x][y++] = c;
            alphabet[c - 'a'] = 1;
            if (y == SIZE) { y = 0; x++; }
        }
    }
}
void findPosition(char matrix[SIZE][SIZE], char c, int *row, int *col) {
    if (c == 'j') c = 'i'; // Treat 'j' as 'i'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char a, char b, char matrix[SIZE][SIZE], char *result) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);
    if (row1 == row2) {
        result[0] = matrix[row1][(col1 + 1) % SIZE];
        result[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = matrix[(row1 + 1) % SIZE][col1];
        result[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        result[0] = matrix[row1][col2];
        result[1] = matrix[row2][col1];
    }
}
void encrypt(char plaintext[], char matrix[SIZE][SIZE], char ciphertext[]) {
    int len = strlen(plaintext), k = 0;
    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < len) ? plaintext[i + 1] : 'x';
        if (a == b) b = 'x'; 
        encryptPair(a, b, matrix, &ciphertext[k]);
        k += 2;
    }
    ciphertext[k] = '\0';
}
int main() {
    char key[50], plaintext[100], ciphertext[100];
    char matrix[SIZE][SIZE];
    printf("Enter the keyword: ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    for (int i = 0; plaintext[i]; i++) {
        plaintext[i] = tolower(plaintext[i]);
        if (plaintext[i] == 'j') plaintext[i] = 'i'; 
    }
    createMatrix(key, matrix);
    printf("5x5 Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    encrypt(plaintext, matrix, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}
