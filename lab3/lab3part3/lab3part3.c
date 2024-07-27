#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int num_rect = 1;

    //prompts user for the number of rectangles to determine if needed to go into the loop
    printf("Please enter the number of rectangles (n): ");
    scanf("%d", &num_rect);
    while(num_rect > 0){
        double a = 0, b = 0, area = 0, width = 0, height = 0;
        printf("Please enter the interval of integration (a b): ");
        scanf("%lf %lf", &a, &b);
        //continuously prompts user for correct range until it meets conditions
        while(b < a){
            printf("Invalid interval!\n\n");
            printf("Please enter the interval of integration (a b): ");
            scanf("%lf %lf", &a, &b);
        }
        
        //caluclates the width of the rectangles
        width = fabs(b - a)/num_rect;

        //sums up the areas of the rectangles
        for (int i = 0; i < num_rect; i++){
            height = exp(-pow((a+(width*i + width*(i+1))/2), 2));
            area += height*width;
        }

        //prints out result
        printf("The integral of e^-x^2 on [%.5lf, %.5lf] with n = %d is: %.5lf", a, b, num_rect, area);
        
        //prompts user again for the number of rectangles
        printf("\n\nPlease enter the number of rectangles (n): ");
        scanf("%d", &num_rect);
    }
    printf("Exiting.");
    return EXIT_SUCCESS;
}
