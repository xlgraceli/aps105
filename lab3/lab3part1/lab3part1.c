#include <stdio.h>

int main(void) {
    char userSign;
    int userNum;
    int sum = 0;
    printf("Enter sequence of numbers to add: ");
    do {
        scanf("%c%d", &userSign, &userNum);
        if (userSign == '-') {
            sum -= userNum;
            printf("Sum is updated to %d\n", sum);
        } else{
            sum += userNum;
            printf("Sum is updated to %d\n", sum);
        }
    } while (sum >= 0);
    printf("Sum fell below zero.\n");
    return 0;
}