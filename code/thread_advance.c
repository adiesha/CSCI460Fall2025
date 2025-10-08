#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // for malloc

struct Args
{
    int a;
    double b;
};


void* compute(void* arg) {
    struct Args* args = (struct Args*) arg;
    printf("a = %d, b = %.2f\n", args->a, args->b);
    double* result = malloc(sizeof(double));
    *result = args->b;

    return result;
}


int main() {
    pthread_t thread;

    struct Args args = {10, 4.1};
    pthread_create(&thread, NULL, compute, &args);
    
    double* returnvalue;
    pthread_join(thread, (void **)&returnvalue);
    printf("Thread returned: %.3f\n", *returnvalue);
    return 0;

}
