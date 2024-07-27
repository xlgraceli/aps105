#include <stdio.h>
#include <stdlib.h>

int main(void){
    int currentHr, currentMin, laterHr, laterMin;
    double tripTime;
    int totalMinutes;
    int flag = 0; //0 for no additional hours from minutes after added, 1 for addition hour added to laterHr from minutes

    printf("Enter current time: ");
    scanf("%d %d", &currentHr, &currentMin);
    printf("Enter trip time: ");
    scanf("%lf", &tripTime);

    //calculations
    //find the future minutes hand
    totalMinutes = (int) (tripTime * 60);
    if ((totalMinutes%60 + currentMin) >= 60){ //for more than or equal to 60 minutes
        laterMin = (totalMinutes%60 + currentMin)%60;
        flag = 1;
    }else{
        laterMin = totalMinutes%60 + currentMin;
    }

    //finding the future hours hand
    if ((totalMinutes/60 + currentHr) >= 24){ //for more than or equal to 24 hours
        laterHr = (totalMinutes/60 + currentHr)%24;
    }else{
        laterHr = totalMinutes/60 + currentHr;
    }

    if (flag == 1){ //to add additional hour due to more than 60 minutes
        laterHr += 1;
    }

    //results
    printf("Current time: %02d:%02d\n", currentHr, currentMin);
    if (currentHr < laterHr){
        printf("Arrival Time is same day %02d:%02d", laterHr, laterMin);
    }else{
        printf("Arrival Time is next day %02d:%02d", laterHr, laterMin);
    }
    
    return EXIT_SUCCESS;
}