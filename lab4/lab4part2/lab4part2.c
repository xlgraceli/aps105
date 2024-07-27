#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isLuckyNum(int num);

int main(void){
    int num, count = 0;
    
    printf("Input an integer: ");
    scanf("%d", &num);
    
    while(num != 0){
        if (isLuckyNum(num)){
            count++;
        }
        printf("Input an integer (0 to stop): ");
        scanf("%d", &num);
    }

    printf("You entered %d lucky number(s)!\n", count);
    return EXIT_SUCCESS;
}

bool isLuckyNum(int num){
    int counter = 0;
    while(num != 0){
        if (num%10 == 7 || num%10 == -7){
            counter++;
        }
        num /= 10;
    }

    if (counter == 3){
        return true;
    }else{
        return false;
    }
}