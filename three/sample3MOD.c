#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int status;

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failure");
        exit(1);
    } else if (pid == 0) {
        printf("I am child PID %ld\n", (long)getpid());
        // insert an appropriate form of the exit() call here
        exit(0);
        // exit(35);
    } else {
        // insert an appropriate form of wait() call here
        wait(&status);
        printf("I am parent PID %d\n", getpid());
        printf("Child [PID %d] exit code is %d\n", pid, WEXITSTATUS(status));
    }
}
