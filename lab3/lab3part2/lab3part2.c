#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){
    //initializing constants and variables
    const double G = 9.81, V = 20, L = 2, PI = 3.14159265;
    double horiDist = 0, targetDist = 0, angle = 0, y = 0, vy = 0, vx = 0, time = 0;
    
    //prompts user continuously for input until it satisfies the conditions
    do{
        printf("Please enter the horizontal distance from the wall between 3 and 30 m:\n");
        scanf("%lf", &horiDist);
    }while (horiDist < 3 || horiDist > 30);
    do{
        printf("Please enter the target height between 3 and 6 m:\n");
        scanf("%lf", &targetDist);
    }while (targetDist < 3 || targetDist > 6);

    //will add 1 degree to angle until |y - targetDist| <= 0.3
    do{
        vx = V*cos(angle*PI/180);
        vy = V*sin(angle*PI/180);
        time = horiDist/vx;
        y = L + vy*time - (1/2.0)*G*pow(time,2);
        angle++;
    }while (fabs(y - targetDist) > 0.3);

    //prints out result
    printf("The angle should be %.2lf\n", angle-1);
    return EXIT_SUCCESS;
}
