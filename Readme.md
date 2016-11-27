#### Assignment assigned by Marzia Mam
### Process Management

1. Compile and run
``` bash

    gcc -std=c11 -lpthread sample1.c -o sample1
    ./sample1
    Before fork
    After fork
    After fork
```

2. fork() function[System call defined in kernel] creates a new process. The return value is the zero
  in the child and the process-id number of the child in the parent,
  or -1 upon error. In the latter case, ERRNO indicates the problem.
  In the child, PROCINFO["pid"] and PROCINFO["ppid"] are updated  to
  reflect the correct values.


       @load "fork"
       ...
       if ((pid = fork()) == 0)
             print "hello from the child"
       else
             print "hello from the parent"

  NB: In Windows fork() alternative CreateProcess()

3. ps utility helps to determine pgid, ppid, pid , you can kill PID and many more ..



12. Run Sample5 while changing its command-line arguments in order to identify the bugs. The following assumes that the name of the executable is sample5.


Explanation : when user didn't provide extra arg vector simple skip, otherwise NULL pointer will works as an executable

If argv[1] is correct then child process address space will be replaced by new execution environment via system call execvp()

If argv[1] is incorrect then it will throw an error and mesage "unkonwn command", To check executable file in system PATH environmental variable,

``` c
    //
    //
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
            printf("builtin command error \"%s\" (status = %d)\n", argv[1], WEXITSTATUS(status));
        } else
            printf("Unknown command \"%s\" (status = %d)\n", argv[1],
                WEXITSTATUS(status));
    }
    printf("[Printed by %d]\n", getpid());

```
If executable is valid but command line options are not valid then option error will be thrown
