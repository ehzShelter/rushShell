#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

#define KYEL "\x1B[33m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"

int rushExit(char** args);
int rushLaunch(char** args);
void rushLoop(void);
int rushExecute(char** args);
char* readLine(void);
char** splitting(char* line);

int main(int argc, char** argv)
{
    printf("%sWelcome to Rush !\n", KMAG);
    rushLoop();
    return EXIT_SUCCESS;
}

int rushExit(char** args)
{
    return 0;
}

// looping the command
void rushLoop(void)
{
    char* line;
    char** args;
    int status;

    do {
        printf("%s$$ ", KCYN);
        line = readLine();
        args = splitting(line);
        status = rushExecute(args);

        free(line);
        free(args);
    } while (status);
}

int rushLaunch(char** args)
{
    int status;

    int pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("err");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("err");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int rushExecute(char** args)
{
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0){
        printf("%sBye\n", KYEL);
        return 0;
    }
    return rushLaunch(args);
}


char* readLine(void)
{
    int bufsize = BUFFER_SIZE;
    int position = 0;
    char* buffer = (char*)malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "something error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += BUFFER_SIZE;
            buffer = (char*)realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "something error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define BUFSIZE 64
// tab enter new line and beep
// Stil confused
#define DELIM " \t\r\n\a"

char** splitting(char* line)
{
    int bufsize = BUFSIZE, position = 0;
    char** tokens = (char**)malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
        fprintf(stderr, "something error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            tokens = (char**)realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "something error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


