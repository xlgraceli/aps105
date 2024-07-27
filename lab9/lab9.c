#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Implement these functions
void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int);
void handleVoltage(LinkedList*, int);
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

int main(void) {
  LinkedList circuit;
  initList(&circuit);
  char command = '\0';
  printf("Welcome to our circuit simulator\n");
  
  // Enter the source voltage!
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);

  while (command != 'Q') {
    command = getCommand();

    switch (command) {
      case 'I':
        handleInsert(&circuit);
        break;
      case 'R':
        handleRemove(&circuit);
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);
        break;
      case 'V':
        handleVoltage(&circuit, voltage);
        break;
      case 'P':
        handlePrint(&circuit);
        break;
      case 'Q':
        handleQuit(&circuit);
        break;
    }
  }
  return 0;
}

// TODO: Implement the insert into ordered list function
void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  
  //checks if labelName exists in list
  Node* checkResistor = circuit->head;
  while (checkResistor != NULL) {
    if (strcmp(labelName, checkResistor->name) == 0) {
        printf("A resistor with %s label already exists.\n", labelName);
        return;
    }
    checkResistor = checkResistor->next;
  }
  
  Node* newResistor = (Node*)malloc(sizeof(Node));
  if (newResistor != NULL){
    newResistor->value = resistance;
    strcpy(newResistor->name, labelName);
    newResistor->next = NULL;
    if (circuit->head == NULL){
        circuit->head = newResistor;
    }else{
        Node** currentResistor = &circuit->head;
        while (*currentResistor != NULL && strcmp(labelName, (*currentResistor)->name) > 0) {
            currentResistor = &((*currentResistor)->next);
        }
        newResistor->next = *currentResistor;
        *currentResistor = newResistor;
    }
  }
}

// TODO: Implement the remove function
void handleRemove(LinkedList* circuit) {
  printf("What's the label of the resistor you want to remove: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  //check if such resistor exists in list
  Node* checkResistor = circuit->head;
  bool isThere = false;
  while (checkResistor != NULL) {
    if (strcmp(labelName, checkResistor->name) == 0) {
        isThere = true;
        break;
    }
    checkResistor = checkResistor->next;
  }

  if (!isThere){
    printf("The resistor with %s label does not exist.\n", labelName);
    return;
  }

  Node* currentResistor = circuit->head;
  Node* prevResistor = NULL;
  while (currentResistor != NULL) {
    if (strcmp(labelName, currentResistor->name) == 0){
        if (prevResistor != NULL) {
            prevResistor->next = currentResistor->next;
        }else{ //first resistor in list
            circuit->head = currentResistor->next;
        }
        free(currentResistor);
        return;
    }
    prevResistor = currentResistor;
    currentResistor = currentResistor->next;
  }
}

// TODO: Implement the function that prints the value of current in the circuit
void handleCurrentCal(LinkedList* circuit, int voltage) {
  double current = 0, equivalentResistor = 0;
  Node* currentResistor = circuit->head;
  while (currentResistor != NULL) {
    equivalentResistor += currentResistor->value;
    currentResistor = currentResistor->next;
  }

  current = voltage / equivalentResistor;
  printf("The current in the circuit is %.6lfA\n", current);
}

// TODO: Implement the function that prints the potential difference across a resistor
void handleVoltage(LinkedList* circuit, int voltage) {
  printf("What's the label of the resistor you want to find the voltage across: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  Node* theResistor = circuit->head;
  bool isThere = false;

  while (theResistor != NULL) {
    if (strcmp(labelName, theResistor->name) == 0) {
        isThere = true;
        break;
    }
    theResistor = theResistor->next;
  }

  if (!isThere){
    printf("The resistor with %s label does not exist.\n", labelName);
    return;
  }else{
    double equivalentResistor = 0;
    Node* currentResistor = circuit->head;
    while (currentResistor != NULL) {
        equivalentResistor += currentResistor->value;
        currentResistor = currentResistor->next;
    }
    double current = voltage / equivalentResistor;
    double voltageOfResistor = current * (theResistor->value);
    printf("Voltage across resistor is %.6lfV", voltageOfResistor);
  }
}

// TODO: they can implement the print function
void handlePrint(LinkedList* circuit) {
  Node* currentResistor = circuit->head;
  while (currentResistor != NULL) {
    printf("%s  %d Ohms\n", currentResistor->name, currentResistor->value);
    currentResistor = currentResistor->next;
  }
}

// TODO: Implement the quit function
void handleQuit(LinkedList* circuit) {
  printf("Removing all resistors in the circuit...\n");
  Node* currentResistor = circuit->head;
  while (currentResistor != NULL) {
    printf("%s  %d Ohms\n", currentResistor->name, currentResistor->value);
    Node* temp = currentResistor;
    currentResistor = currentResistor->next;
    free(temp);
  }
  circuit->head = NULL; 
}
