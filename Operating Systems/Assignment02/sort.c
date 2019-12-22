#include <stdio.h>
#include <stdlib.h>  // header for comparison functions
#include<string.h>
// #define ELEMENTS(x) (sizeof(x) / sizeof(x)[0])

int LIST_SIZE = 10;

typedef struct state {
    char name[3];
} state;

// Prototype for state comparison method required for qsort()
int compare_states(const void *a, const void *b);
void printResults(state arr[], int length);

int main(int argc, char const *argv[])
{
    state list[LIST_SIZE];
    //size_t length = ELEMENTS(list);
    int i = 0;

    memset(&list, 0, sizeof(list)+1);  // CHECK LENGTH VALUE
    while((LIST_SIZE > i++) && (scanf("%s", list[i].name) != EOF)){}
    size_t actual = sizeof(list) / sizeof(state) + 1;
    qsort(list, actual, sizeof(state), compare_states);
    printResults(list, actual);
    
    return 0;
}

// Courtesy of gnu.org/software/libc/manual/html_node/Comparison-Functions.html
int compare_states(const void *a, const void *b) {
    const state *da = (const state *) a;
    const state *db = (const state *) b;
    return strcmp(da->name, db->name);
}

void printResults(state arr[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%s\n", arr[i].name);      
    }
}