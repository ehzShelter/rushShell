#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define KRED "\x1B[31m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"

void dummy(void);

int main(void)
{
    printf("%sMain FUNCTION : \n", KCYN);
    fprintf(stdout, "OS is assigned me to PID #%d of parent process #%d and group #%d\n", getpid(), getppid(), getgid());
    puts("");
    dummy();
}

void dummy(void)
{
    static int counter = 0;
    pid_t thePID = fork();

    if (thePID == 0) {
        counter++;
        printf("%sfork() return to CHILD PID #%d\n", KYEL, thePID);
        puts("");
        printf("%schild process IMAGE : \n", KYEL);
        fprintf(stdout, "I am the process #%d of parent #%d .. group #%d\n", getpid(), getppid(), getgid());
        fprintf(stdout, "But the parent give me #%d\n", thePID);
        puts("");
        printf("static counter in dummy() function : %d\n", counter);
        exit(0);
    } else if (thePID > 0) {
        counter++;
        printf("%sfork() return to PARENT PID #%d\n", KMAG, thePID);
        wait(&thePID);
        printf("%sparent process IMAGE : \n", KMAG);
        fprintf(stdout, "I am the process #%d of parent #%d ..group #%d\n", getpid(), getppid(), getgid());
        puts("");
        printf("static counter in dummy() function : %d\n", counter);
        exit(0);
    } else {
        fprintf(stderr, "%sSorry process cannot be created", KRED);
        exit(-1);
    }
}
