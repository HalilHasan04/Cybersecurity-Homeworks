#include <stdio.h>
#include <string.h>

void break_caesar(char *cipher) {
    char temp[100];
    for (int k = 1; k < 26; k++) {
        strcpy(temp, cipher);
        for (int i = 0; temp[i] != '\0'; i++) {
            if (temp[i] >= 'A' && temp[i] <= 'Z') {
                temp[i] = (temp[i] - 'A' - k + 26) % 26 + 'A';
            }
        }
        printf("Key %d: %s\n", k, temp);
    }
}

int main() {
    char code[] = "WKLV LV D VHFUHW PHVVDJH";
    break_caesar(code);
    return 0;
}
