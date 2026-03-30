#include <stdio.h>
#include <string.h>

void find_repeats(char *text) {
    int n = strlen(text);
    for (int i = 0; i < n - 3; i++) {
        for (int j = i + 1; j < n - 3; j++) {
            if (strncmp(&text[i], &text[j], 3) == 0) {
                printf("Found \"%.3s\": Pos %d & Pos %d -> Distance: %d\n", 
                        &text[i], i, j, j - i);
            }
        }
    }
}

int main() {
    char cipher[] = "ABCXYZABCQWEABDSFJJDSF";
    find_repeats(cipher);
    return 0;
}