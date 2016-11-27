#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fputs("Usage: must supply a limit value\n", stderr);
        exit(1);
    }

    int limit = atoi(argv[1]); // ascii to integer

    // two fork call
    fork();
    fork();
    printf("PID: %d\n", getpid());
    for (int k = 0; k < limit; k++) {
        printf("%d\n", k);
    }

    return 0;
}
