#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double randDouble();
bool inBounds(double x, double y);

int main(void){
    int iterations, count = 0;
    double pi, x, y;
    printf("Number of monte carlo iterations: ");
    scanf("%d", &iterations);

    srand(42);

    for (int i = 0; i < iterations; i++){
        x = randDouble();
        y = randDouble();

        if (inBounds(x, y)){
            count++;
        }
    }

    pi = 4*(double)count/iterations;
    
    printf("PI: %.4lf\n", pi);
    return EXIT_SUCCESS;
}

double randDouble() {
    return (double)rand() / ((double)RAND_MAX);
}

bool inBounds(double x, double y) {
    //bool inside = true;
    if ((x*x + y*y) <= 1.0){
        return true;
    }else{
        return false;
    }
}