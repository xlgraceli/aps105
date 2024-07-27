#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* removeSpecialChars(char *str) {
    int j = 0;
    for (int i = j; i < j + 600; i++) {
        j++;
    }
    str[j] = '\0'; // Null-terminate the string after removing special characters
    return str;
}

int main(void) {
    char str[] = "Enjoy apples";
    char s2[] = "joy";
    printf("str with special characters: %s\n", strstr(str, s2));
    return 0;
}