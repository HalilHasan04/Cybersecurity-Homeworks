#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rc4_process(unsigned char *key, int key_len, unsigned char *data, int data_len) {
    unsigned char s[256];
    for (int i = 0; i < 256; i++) s[i] = i;

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % key_len]) % 256;
        unsigned char temp = s[i]; s[i] = s[j]; s[j] = temp;
    }

    int i = 0; j = 0;
    for (int k = 0; k < data_len; k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        unsigned char temp = s[i]; s[i] = s[j]; s[j] = temp;
        data[k] ^= s[(s[i] + s[j]) % 256];
    }
}

int main() {
    FILE *fIn = fopen("input.txt", "rb");
    FILE *fKey = fopen("key.txt", "r");
    FILE *fOut = fopen("output.enc", "wb");

    if (!fIn || !fKey || !fOut) {
        printf("Greshka pri otvaryane na failovete!\n");
        return 1;
    }

    unsigned char key[256];
    fgets((char*)key, 256, fKey);
    int key_len = strlen((char*)key);

    fseek(fIn, 0, SEEK_END);
    long size = ftell(fIn);
    fseek(fIn, 0, SEEK_SET);

    unsigned char *buffer = malloc(size);
    fread(buffer, 1, size, fIn);

    rc4_process(key, key_len, buffer, size);

    fwrite(buffer, 1, size, fOut);

    printf("Failat e obraboten uspeshno!\n");

    free(buffer);
    fclose(fIn); fclose(fKey); fclose(fOut);
    return 0;
}
