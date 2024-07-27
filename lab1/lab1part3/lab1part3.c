#include <stdio.h>
#include <math.h>

int main(void) {
    double circum, accel, radiusKm, radiusM, mass, velocity;
    const double pi = 3.1415952654, gravity = 6.6726;
    printf("Circumference (km) of planet? ");
    scanf("%lf", &circum);
    printf("Acceleration due to gravity (m/s^2) on planet? ");
    scanf("%lf", &accel);

    //calculating values
    radiusKm = circum/pi/2;
    radiusM = radiusKm*1000;
    
    mass = accel * pow(radiusM, 2) / (gravity*pow(10, -11)) / pow(10,21); 
    velocity = sqrt(2*(gravity*pow(10,-20))*(mass*pow(10,21))/radiusKm);
    
    printf("\nCalculating the escape velocity...\n");
    printf("Planet radius: %.1lf km\n", radiusKm);
    printf("Planet mass: %.1lf x 10^21 kg\n", mass);
    printf("Escape velocity: %.1lf km/s", velocity);
    
    return 0;
}