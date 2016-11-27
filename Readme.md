#### Assignment assigned by Marzia Mam
### Process Management

###### 1.
Compile and run
``` bash

    gcc -std=c11 -lpthread sample1.c -o sample1
    ./sample1
    Before fork
    After fork
    After fork
```

###### 2.
fork() function[System call defined in kernel] creates a new process. The return value is the zero
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

######3.
ps utility helps to determine pgid, ppid, pid , you can kill PID and many more ..
for instance, kill [Running PID]

######6.
Usually, parent prints first most of the time, though this may vary due to OS architecture

But reverse is also true , Sometimes child prints first due to race condition,
To ensure parent prints first , we can use signal locking machanism.

######7.
WIFEXITED(status)
 returns true if the child terminated normally, that is, by calling exit(0) or whatever exit(35)

 This exit status is trapped by wait(int* status) call via pointer

    waitpid(-1, &status, 0);
    equivalent to
    wait(&status);

```c
    // ...
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
```

######8.

The interaction between the exit() and wait() are complementary.
Description earlier code snippet


######9.
The string "End of program" will be printed when child process is not replaced by execvp()  call and when if and else macro condition will not be fulfilled.

######10. EXPLANATION of previous context

        In execl() wee have to specify FULL BINARY PATH location, and executable file should have proper executable permission

        In execl("exe", argv[1], argv[2], argv[3],....,argv[N], NULL);
        Here argv[1] is simply ignored

        For that reason, Here "Lakers" strings is simply ignored
        execl("/usr/bin/cal", "Lakers", "10", "1988", NULL);

        On the other hand,

        execvp() last letter 'p' stands for path, that means that binary should be in $PATH environmental variable whatever the location.
        That's why we have used "cal" NOT "/bin/cal"

``` c
// ....

    char* m_args[] = { "July 2050", "7", "2050", NULL };

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
```

######11.
Significance is describled earlier

######12.
Run Sample5 while changing its command-line arguments in order to identify the bugs. The following assumes that the name of the executable is sample5.


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
