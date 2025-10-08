#include <stdio.h>     // for printf()
#include <pthread.h>   // for POSIX threads API
#include <unistd.h>    // for sleep()

// any function that can be run by a posix thread should have the 
// following pattern 
// void* func(void* arg)
// at most there could be one arguement here.
void *compute() {
    sleep(2);
    printf("computing something in thread 1\n");
    return NULL;
}

int main () {


    pthread_t thread1;
    
    int return_create = pthread_create(&thread1, NULL, compute, NULL);
    
    printf("Thread creation returned: %d\n" , return_create);
    if (return_create == 0)
        printf("Thread creation was successfull\n");
    
    // you can use the second arguement to store 
    // the return value of the thread
    pthread_join(thread1, NULL);
    // sleep(3);
    return 0;
}