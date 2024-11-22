#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generateTable(char key[], char table[SIZE][SIZE]) {
    int flag[26] = {0};
    int i, j, k = 0;
    char letter;
    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'J') key[i] = 'I';
        if (!flag[key[i] - 'A']) {
            flag[key[i] - 'A'] = 1;
            table[k / SIZE][k % SIZE] = key[i];
            k++;
        }
    }
    for (letter = 'A'; letter <= 'Z'; letter++) {
        if (letter == 'J') continue;
        if (!flag[letter - 'A']) {
            table[k / SIZE][k % SIZE] = letter;
            k++;
        }
    }
}
void findPosition(char table[SIZE][SIZE], char c, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (table[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt a pair of characters
void decryptPair(char table[SIZE][SIZE], char a, char b, char *x, char *y) {
    int r1, c1, r2, c2;
    findPosition(table, a, &r1, &c1);
    findPosition(table, b, &r2, &c2);
    if (r1 == r2) {
        *x = table[r1][(c1 + SIZE - 1) % SIZE];
        *y = table[r2][(c2 + SIZE - 1) % SIZE];
    } else if (c1 == c2) {
        *x = table[(r1 + SIZE - 1) % SIZE][c1];
        *y = table[(r2 + SIZE - 1) % SIZE][c2];
    } else {
        *x = table[r1][c2];
        *y = table[r2][c1];
    }
}
void decryptPlayfair(char ciphertext[], char key[], char plaintext[]) {
    char table[SIZE][SIZE];
    int i, k = 0;
    generateTable(key, table);
    for (i = 0; i < strlen(ciphertext); i += 2) {
        char x, y;
        decryptPair(table, ciphertext[i], ciphertext[i + 1], &x, &y);
        plaintext[k++] = x;
        plaintext[k++] = y;
    }
    plaintext[k] = '\0';
}
int main() {
    char key[] = "KEYWORD"; 
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[256];
    decryptPlayfair(ciphertext, key, plaintext);
    printf("Decrypted Text: %s\n", plaintext);
    return 0;
}
