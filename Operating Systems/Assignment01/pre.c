#include <stdio.h>
#include <string.h>

// Global variable to define desired list size.
int LIST_SIZE = 10;

// A wrapper type to store state input
typedef struct state {
    char name[2];
    int pop;
} state;

// Prototype for display method
void printResults(state arr[], int length);

int main(int argc, char const *argv[])
{
    state list[LIST_SIZE];
    char state[2];
    int population, i = 0;

    // Loop construct takes user input until list is full or CTRL-D entered.
    while((i < LIST_SIZE) && (scanf("%2s" "%d", state, &population) != EOF)) {
        strcpy(list[i].name, state);
        list[i].pop = population;
        ++i;
    }
    printResults(list, (LIST_SIZE - (LIST_SIZE - i)));

    return 0;
}

void printResults(state arr[], int length) {
    for (int i = 0; i < length; ++i) {
        if (arr[i].pop >= 10) 
            printf("%s\n", arr[i].name);
    }
}