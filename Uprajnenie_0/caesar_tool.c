#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *keyFile = fopen("key.txt", "r");
    int key = 0;
    if (keyFile) {
        fscanf(keyFile, "%d", &key);
        fclose(keyFile);
    }

    FILE *in = fopen("plaintext.txt", "r");
    FILE *out = fopen("encrypted.txt", "w");

    if (in == NULL || out == NULL) return 1;

    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            fputc((ch - base + key) % 26 + base, out);
        } else {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}