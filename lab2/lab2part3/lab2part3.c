#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){
    const double K = 8.9875*pow(10,9); //Nm^2/C^2
    double force, q1_num, q2_num, distance;
    char q1_units1, q1_units2, q2_units1, q2_units2;

    //prompts user for info
    printf("Enter the value of the two charges separated by a space: ");
    scanf("%lf%c%c %lf%c%c", &q1_num, &q1_units1, &q1_units2, &q2_num, &q2_units1, &q2_units2);
    printf("Enter distance between charges in metres: ");
    scanf("%lf", &distance);

    //converting units to coulomb
    if (q1_units1 == 'n'){
        q1_num *= pow(10, -9);
    }else{
        q1_num *= pow(10, -6);
    }

    if (q2_units1 == 'n'){
        q2_num *= pow(10, -9);
    }else{
        q2_num *= pow(10, -6);
    }

    //calculating force
    force = K * fabs(q1_num * q2_num) / pow(distance, 2);
    
    //results
    if (force < pow(10, -6)){
        printf("The force between charges is %.2lf%c%c (less than 1uN)", force*pow(10, 9), 'n', 'N');
    }else if (force < pow(10, -3)){
        printf("The force between charges is %.2lf%c%c (less than 1mN)", force*pow(10, 6), 'u', 'N');
    }else if (force < 1){
        printf("The force between charges is %.2lf%c%c (less than 1N)", force*pow(10, 3), 'u', 'N');
    }else{
        printf("The force between charges is %.2lf%c (1N or greater)", force, 'N');
    }
    
    return EXIT_SUCCESS;
}