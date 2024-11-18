#include <stdio.h>
#include <string.h>
#include <ctype.h>
void processText(char text[], char key[], int isEncrypt) {
    char reverseKey[26];
    if (!isEncrypt) {
        for (int i = 0; i < 26; i++) 
            reverseKey[key[i] - 'a'] = 'a' + i;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            char offset = islower(c) ? 'a' : 'A';
            text[i] = isEncrypt ? key[tolower(c) - 'a'] : reverseKey[tolower(c) - 'a'];
            if (isupper(c)) text[i] = toupper(text[i]);
        }
    }
}
int main() {
    char key[27], text[100];
    int choice;
    printf("Enter substitution key (26 unique lowercase letters): ");
    scanf("%s", key);
    printf("Enter text: ");
    getchar(); 
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("1. Encrypt\n2. Decrypt\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1 || choice == 2) {
        processText(text, key, choice == 1);
        printf("Result: %s\n", text);
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}
