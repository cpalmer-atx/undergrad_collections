/*
    Written by: Chad Palmer
    CS-4328: Operating Systems
    Lab 3b: Simulate two concurrent threads with consideration given to mutual exclusion

    Helpful References:
    https://dzone.com/articles/how-can-we-controlschedule-execution-of-threads-in
    http://alumni.media.mit.edu/~panwei/cs23/thread_tutorial.html
    https://www.youtube.com/watch?v=VAV2h1GdgE0
*/

#include <unistd.h>                                     // For sleep()
#include <pthread.h>                                    // pthread library
#include <stdio.h>

#define LOOPCOUNT 10
#define BLOCKSIZE 5

int is_done = 0;                                        // Thread completion indicator
pthread_mutex_t mutex;                                  // Mutex "lock" for is_done
pthread_cond_t t1_done;                                 // Conditional wait variable for t1
pthread_cond_t t2_done;                                 // Conditional wait variable for t2

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


void* t1_method(void* ptr) {                            // Consideration given to mutex
    int i, j;
    i = 0;
    while (i < LOOPCOUNT) {
        pthread_mutex_lock(&mutex);                     // Acquire mutex & lock it             
        if (is_done) {
            pthread_cond_wait(&t2_done, &mutex);        // wait for signal from T2 to proceed
        }
        else {        
            for (j = 0; j < BLOCKSIZE; j++) {           // Print a single block
                print(i+1, "AAAAAAAAA");                // (5 consecutive rows of AAAAAAAAA)
                sleep(1);
            }
            is_done = 1;                                // set done flag to true  
            printf("\n");
            i++;
               
            pthread_cond_broadcast(&t1_done);           // Signal to T2 that T1 block has finished
        }
        pthread_mutex_unlock(&mutex);                   // Unlock mutex
    }
}

void* t2_method(void* ptr) {                            // Consideration given to mutex
    int i, j;
    i = 0;
    while (i < LOOPCOUNT) {
        pthread_mutex_lock(&mutex);                     // Acquire mutex & lock it
        if (!is_done) {
            pthread_cond_wait(&t1_done, &mutex);        // wait for signal from T1 to proceed
        }
        else {                 
            for (j = 0; j < BLOCKSIZE; j++) {           // Print a single block
                print(i+1, "BBBBBBBBB");                // (5 consecutive rows of BBBBBBBBB)
                sleep(1);
            }
            is_done = 0;                                // set done flag to false
            printf("\n");
            i++;
               
            pthread_cond_broadcast(&t2_done);           // Signal to T1 that T2 block has finished               
        }
        pthread_mutex_unlock(&mutex);                   // Unlock mutex
    }
}

void* print(int block, char* thread) { printf("%d: %s\n", block, thread); }