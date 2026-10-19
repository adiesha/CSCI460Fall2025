#include <stdio.h>
#include <unistd.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void parent() { // Fixed typo from partent
    printf("%sMy pid is %d and this is the parent process %s\n", KRED, getpid(), KNRM);
    sleep(2);
    return;
}

void child() {
    printf("%sThis is the child process\n%s", KGRN, KNRM);
    sleep(1);    
}

int main() {
    int pid = fork();
    
    if (pid < 0) {
        printf("Error occurred during forking\n");
        return 1;
    } 
    else if (pid == 0) { // This is the child process
        // CORRECTED: fork() returns exactly 0 to the child process
        printf("%sSince the returned fork pid value is exactly %d, this must be the child process.\n", KGRN, pid);
        printf("My actual PID using getpid() is: %d\n", getpid());
        printf("Let's invoke the child method%s\n", KNRM);
        child();
    } 
    else { // This is the parent process
        // CORRECTED: fork() returns the child's real PID (greater than 0) to the parent
        printf("%sSince the returned fork pid value is %d (greater than 0), this must be the parent process.\n", KRED, pid);
        printf("And the actual PID of this parent process is %d\n", getpid());
        printf("For the parent, the returned fork value (child's PID) and actual parent PID are different.\n");
        printf("Returned fork value: %d | Actual Parent PID: %d\n", pid, getpid()); // Added newline
        printf("Let's invoke the parent function in this process.\n%s", KNRM);
        parent();
    }
    
    return 0;
}
