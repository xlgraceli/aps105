#include <stdio.h>

int main(void) {
    double tempf, tempc, tempAway, tempNice = 22;
    tempNice = tempNice/(5.0/9)+32;
    printf("Enter the thermostat temperature: ");
    scanf("%lf", &tempf);
    tempc = (tempf - 32)*(5.0/9);
    printf("The temperature in Celsius is: %.1lf\n\n", tempc);
    tempAway = tempf - tempNice;
    printf("You are %.1lf degrees Fahrenheit away from a nice 22 degrees Celsius.", tempAway);
    return 0;
}