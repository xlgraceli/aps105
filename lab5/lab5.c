#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/* Given Functions */
void shuffle_cases(int cases[], int cases_size);
void offer(int cases[], int cases_size, int initial_amount);
int remove_case_and_get_amount(int cases[], int cases_size, int index);

/* Your Functions */
int pick_case_index(int cases[], int cases_size);
bool get_decision(void);
int cases_average(int cases[], int cases_size, int initial_amount);
int cases_remaining(int cases[], int cases_size);
int get_last_remaining_case(int cases[], int cases_size);
void eliminate_cases(int cases[], int cases_size, int eliminated);

int main(void) {
    int cases[] = {
        0, 1, 5, 10, 25, 50, 75, 100, 200,
        300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000,
        75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000,
    };
    int cases_size = ARRAY_SIZE(cases);

    shuffle_cases(cases, cases_size);

    printf("First, pick a case to keep.\n");
    int initial_index = pick_case_index(cases, cases_size);
    int initial_amount = remove_case_and_get_amount(cases, cases_size, initial_index);
    printf("You picked %d, looks like a keeper.\n", initial_index + 1);

    eliminate_cases(cases, cases_size, 6);
    offer(cases, cases_size, initial_amount);

    eliminate_cases(cases, cases_size, 5);
    offer(cases, cases_size, initial_amount);

    eliminate_cases(cases, cases_size, 4);
    offer(cases, cases_size, initial_amount);

    eliminate_cases(cases, cases_size, 3);
    offer(cases, cases_size, initial_amount);

    eliminate_cases(cases, cases_size, 2);
    offer(cases, cases_size, initial_amount);

    while (cases_remaining(cases, cases_size) > 1) {
        eliminate_cases(cases, cases_size, 1);
        offer(cases, cases_size, initial_amount);
    }

    int last_case = get_last_remaining_case(cases, cases_size);
    int last_amount = cases[last_case];
    printf("\nDo you want to swap your case with case %d?\n", last_case + 1);
    bool decision = get_decision();

    if (decision) {
        printf("\nYour initial case had $%d.\n", initial_amount);
        printf("You won $%d.\n", last_amount);
    } else {
        printf("\nThe last case had $%d.\n", last_amount);
        printf("You won $%d.\n", initial_amount);
    }
    return 0;
}

//randomizes the order of cases array elements
void shuffle_cases(int cases[], int cases_size) {
    srand(42);
    for (int shuffle = 0; shuffle < 100; ++shuffle) {
        for (int i = 0; i < cases_size; ++i) {
            int j = rand() % cases_size;
            int temp = cases[i];
            cases[i] = cases[j];
            cases[j] = temp;
        }
    }
}

//marks the user's picked case as removed and returns its value
int remove_case_and_get_amount(int cases[], int cases_size, int index) {
    int amount = cases[index];
    cases[index] = -1;
    return amount;
}

//generates an offer based on remaining case values and the initial pick's value, concluding the game if accepted
void offer(int cases[], int cases_size, int initial_amount) {
    int offer_amount = cases_average(cases, cases_size, initial_amount);
    printf("\nYour offer to quit now is $%d, deal or no deal?.\n", offer_amount);
    bool deal = get_decision();
    if (deal) {
        printf("\nYour case was worth: $%d\n", initial_amount);
        printf("You walked away with $%d.\n", offer_amount);
        exit(0);
    }
}

//returns case index that the user picked
int pick_case_index(int cases[], int cases_size){
    int case_num = 0;
    
    printf("Eligible cases: ");
    //prints out eligible cases
    for (int i = 0; i < cases_size; i++){
        if (cases[i] != -1){
            printf("%d ", i+1);
        }
    }

    //prompts user for valid case
    do{
        printf("\nPick a case: ");
        scanf("%d", &case_num);
    }while(case_num < 1 || case_num > 26 || cases[case_num - 1] == -1);
    
    return case_num - 1;
}

//Queries the user for a yes/no decision (1 or 0)
bool get_decision(void){
    int decision = 0;
    do {
        printf("Decide now (0 for no, 1 for yes): ");
        scanf("%d", &decision);
    }while (decision != 0 && decision != 1);

    return decision;
}

//Calculates the average value of non-eliminated case
int cases_average(int cases[], int cases_size, int initial_amount){
    int sum = 0, avg, count = 0;
    for (int i = 0; i < cases_size; i++){
        if (cases[i] != -1){
            sum += cases[i];
            count++;
        }
    }
    sum += initial_amount;
    count++;
    avg = sum/count;
    return avg;
}

//Prints how many cases it will eliminate
void eliminate_cases(int cases[], int cases_size, int eliminated){
    int index, amount;
    printf("\nOpen %d case(s) to eliminate\n", eliminated);
    for (int i = 0; i < eliminated; i++){
        index = pick_case_index(cases, cases_size);
        amount = remove_case_and_get_amount(cases, cases_size, index);
        printf("Case %d is worth $%d, it's gone now.\n", index+1, amount);
    }
}

//returns the last case index (non-eliminated one)
int get_last_remaining_case ( int cases [] , int cases_size ) {
    int last_case_index = 0;
    while (cases[last_case_index] == -1){
        last_case_index++;
    }
    return last_case_index;
}

//returns how many cases remain in the game
int cases_remaining ( int cases [] , int cases_size ) {
    int count = 0;
    for (int i = 0; i < cases_size; i++){
        if (cases[i] != -1){
            count++;
        }
    }
    return count;
}