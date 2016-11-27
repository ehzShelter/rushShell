#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* This program has a few bugs that must be fixed */
int main(int argc, char* argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Unable to fork(): ");
        exit(errno); /* errno is a global variable declared in errno.h */
    }
    if (pid == 0) /* child */
    {
        printf("Child PID is %d\n", getpid());
        printf("Running \"%s\" in child\n", argv[1]);
        execvp(argv[1], &argv[1]);
    } else { /* parent */
        int status;
        pid_t who_stop;

        printf("Parent PID is %d\n", getpid());

        who_stop = wait(&status);
        if (WEXITSTATUS(status) == 0)
            printf("Successful completion of child %d\n", who_stop);
        else
            printf("Unknown command \"%s\" (status = %d)\n", argv[1],
                WEXITSTATUS(status));
    }
    printf("[Printed by %d]\n", getpid());
    return 0;
}
