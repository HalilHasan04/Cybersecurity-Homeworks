#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

int dictionary_attack(const char *target_hash, const char *dict_file, char *found_pass);
int pin_brute_force(const char *target_hash, char *found_pass);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Употреба: %s <shadow_file> <dictionary_file>\n", argv[0]);
        return 1;
    }

    FILE *shadow_fp = fopen(argv[1], "r");
    if (!shadow_fp) {
        perror("Грешка при отваряне на shadow файла");
        return 1;
    }

    char line[512];
    char found_pass[256];

    printf("--- Резултати ---\n");

    while (fgets(line, sizeof(line), shadow_fp)) {
        line[strcspn(line, "\n")] = 0;

        char *username = strtok(line, ":");
        char *hash = strtok(NULL, ":");

        if (!username || !hash || hash[0] == '*' || hash[0] == '!') continue;

        if (dictionary_attack(hash, argv[2], found_pass)) {
            printf("%s : %s (dictionary)\n", username, found_pass);
        } 
        else if (pin_brute_force(hash, found_pass)) {
            printf("%s : %s (brute-force)\n", username, found_pass);
        } 
        else {
            printf("%s : [НЕРАЗБИТА]\n", username);
        }
    }

    fclose(shadow_fp);
    return 0;
}

int dictionary_attack(const char *target_hash, const char *dict_file, char *found_pass) {
    FILE *file = fopen(dict_file, "r");
    if (!file) return 0;

    char word[256];
    while (fgets(word, sizeof(word), file)) {
        word[strcspn(word, "\n")] = 0;

        char *computed = crypt(word, target_hash);
        if (computed && strcmp(computed, target_hash) == 0) {
            strcpy(found_pass, word);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int pin_brute_force(const char *target_hash, char *found_pass) {
    char guess[5];
    for (int i = 0; i <= 9999; i++) {
        sprintf(guess, "%04d", i);

        char *computed = crypt(guess, target_hash);
        if (computed && strcmp(computed, target_hash) == 0) {
            strcpy(found_pass, guess);
            return 1;
        }
    }
    return 0;
}
