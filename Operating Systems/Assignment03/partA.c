/*
    Written by: Chad Palmer
    CS-4328: Operating Systems
    Lab 3b: Simulate two concurrent threads without consideration given to mutual exclusion

    Helpful References:
    https://dzone.com/articles/how-can-we-controlschedule-execution-of-threads-in
    http://alumni.media.mit.edu/~panwei/cs23/thread_tutorial.html
    https://www.youtube.com/watch?v=VAV2h1GdgE0
*/

#include <unistd.h>                             // For sleep()
#include <pthread.h>                            // pthread library
#include <stdio.h>

#define LOOPCOUNT 10
#define BLOCKSIZE 5

//Prototypes
void* print(int block, char* thread);
void* t1_method(void* ptr);
void* t2_method(void* ptr);

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, (void *(*)(void*))t1_method, NULL );
    pthread_create(&t2, NULL, (void *(*)(void*))t2_method, NULL );

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_exit(0);
}

void* t1_method(void* ptr) {                    // No mutex considered
    int i, j;
    i = 0;
    
    while (i < LOOPCOUNT) {
        for (j = 0; j < BLOCKSIZE; j++) {
        print(i+1, "AAAAAAAAA");
        sleep(1);
        }
        printf("\n");
        i++;
    }   
}

void* t2_method(void* ptr) {                    // No mutex considered
    int i, j;
    i = 0;
    
    while (i < LOOPCOUNT) {
        for (j = 0; j < BLOCKSIZE; j++) {
        print(i+1, "BBBBBBBBB");
        sleep(1);
        }
        printf("\n");
        i++;
    }
}

void* print(int block, char* thread) { printf("%d: %s\n", block, thread); }