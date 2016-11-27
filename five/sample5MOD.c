#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int isFile(const char* systemPath)
{
    // for more run $ man      stat
    // struct stat store information of files
    struct stat buf = {};
    stat(systemPath, &buf);
    return S_ISREG(buf.st_mode);
}

// http://stackoverflow.com/questions/12765010/c-test-for-file-existence-before-calling-execvp

int isExecutableInPath(const char* name)
{
    char* systemPath = getenv("PATH");
    // printf("%s \n", systemPath);
    int found = 0;

    if (!systemPath) {
        return 0;
    }

    // allocation most possible highest value
    char* localPATH = (char*)calloc(strlen(systemPath), sizeof(char));

    char* item = strtok(systemPath, ":");
    while (item && (!found)) {
        sprintf(localPATH, "%s/%s", item, name);
        // printf("Testing %s\n", localPATH);
        if (isFile(localPATH) && !(access(localPATH, F_OK) || access(localPATH, X_OK))) {
            found = 1;
        }
        item = strtok(NULL, ":");
    }

    free(localPATH);
    return found;
}

int main(int argc, char* argv[])
{
    int status;
    pid_t pid = fork();
    if (pid < 0) {
        perror("Unable to fork(): ");
        exit(errno);
    }

    if (pid == 0) /* child */
    {
        if (argc >= 2) {
            printf("Child PID is %d\n", getpid());
            execvp(argv[1], &argv[1]);
            if (isExecutableInPath(argv[1])) {
            } else {
                exit(-1);
            }
            printf("Running \"%s\" in child\n", argv[1]);
        } else {
            //
        }
    } else { /* parent */

        printf("Parent PID is %d\n", getpid());

        pid_t who_stop = wait(&status);
        if (WEXITSTATUS(status) == 0)
            printf("Successful completion of child %d\n", who_stop);

        else if (WEXITSTATUS(status) > 0 && 255 < WEXITSTATUS(status)) {
            printf("builtin command erro \"%s\" (status = %d)\n", argv[1], WEXITSTATUS(status));
        } else
            printf("Unknown command \"%s\" (status = %d)\n", argv[1],
                WEXITSTATUS(status));
    }
    printf("[Printed by %d]\n", getpid());
    return 0;
}
