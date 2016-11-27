#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char* m_args[] = { "July 2050", "7", "2050", NULL };

    printf("I am process %d, created by process %d\n", getpid(),
        getppid());

// #if 1
#ifdef ULIMATRA
    printf("Using execl()\n");
    // execl("/usr/bin/cal", "" , "10", "1988", NULL);
    execl("/usr/bin/cal", "Lakers", "10", "1988", NULL);
#else
    printf("Using execvp()\n");
    // Only first execvp will execute, because this will replace child image
    execvp("cal", m_args);
    // execvp("foo", m_args);
#endif
    printf("End of program\n");
    return 0;
}
