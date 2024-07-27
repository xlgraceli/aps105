#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    const double PI = 3.14159265;
    double sideA, sideB, sideC, alpha, beta, gamma;
    printf("Enter the length of side A: ");
    scanf("%lf", &sideA);
    printf("Enter the length of side B: ");
    scanf("%lf", &sideB);
    printf("Enter the measure of angle alpha in degrees: ");
    scanf("%lf", &alpha);

    //convert degrees to radians
    alpha = alpha * PI / 180;

    //calculating angles in radians
    beta = asin(sideB*sin(alpha)/sideA);
    gamma = PI - alpha - beta;

    //finding side C
    sideC = sideA*sin(gamma)/sin(alpha);

    //converting back to degrees
    alpha = alpha * 180/PI;
    beta = beta * 180/PI;
    gamma = gamma * 180/PI;

    printf("\nResults:\n");
    printf("Side A: %.2lf\n", sideA);
    printf("Side B: %.2lf\n", sideB);
    printf("Side C: %.2lf\n", sideC);
    printf("Angle Alpha: %.2lf degrees\n", alpha);
    printf("Angle Beta: %.2lf degrees \n", beta);
    printf("Angle Gamma: %.2lf degrees", gamma);
    return EXIT_SUCCESS;
}