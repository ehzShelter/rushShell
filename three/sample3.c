#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid, child;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork failure");
        exit(1);
    } else if (pid == 0) {
        /* code executed in child */
        printf("I am child PID %ld\n", (long)getpid());
        /* insert an appropriate form of the exit() call here */
    } else {
        /* insert an appropriate form of wait() call here */
        printf("I am parent PID %d\n", getpid());
        printf("Child [PID %d] exit code is %d\n",
            child, WEXITSTATUS(status));
    }
}
