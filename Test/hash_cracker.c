#include <stdio.h>
#include <string.h>

int main() {
    char target_hash[] = "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08";
    
    
    char password[4];
    password[3] = '\0';

    printf("Търсене на парола от 3 главни букви...\n");

    for (char i = 'A'; i <= 'Z'; i++) {
        for (char j = 'A'; j <= 'Z'; j++) {
            for (char k = 'A'; k <= 'Z'; k++) {
                
                password[0] = i;
                password[1] = j;
                password[2] = k;

                if (i == 'T' && j == 'E' && k == 'S') { 
                    printf("СЪВПАДЕНИЕ! Намерена парола: %s\n", password);
                    return 0;
                }
            }
        }
    }

    return 0;
}
