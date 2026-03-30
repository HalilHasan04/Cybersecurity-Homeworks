#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fText = fopen("encrypted.txt", "r");
    FILE *fKey = fopen("key.txt", "r");
    FILE *fOut = fopen("decrypted.txt", "w");

    char key[100];
    if (fKey) fscanf(fKey, "%s", key);
    
    int ch, key_idx = 0;
    int key_len = strlen(key);

    while ((ch = fgetc(fText)) != EOF) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int k_shift = toupper(key[key_idx % key_len]) - 'A';
            int decrypted = (toupper(ch) - 'A' - k_shift + 26) % 26 + 'A';
            fputc(isupper(ch) ? decrypted : tolower(decrypted), fOut);
            key_idx++;
        } else {
            fputc(ch, fOut);
        }
    }

    fclose(fText); fclose(fKey); fclose(fOut);
    return 0;
}
