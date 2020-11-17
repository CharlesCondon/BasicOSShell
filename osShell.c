/*
 * author: Charles Condon
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 10

// function to match user input with basic built-in commands
void builtIn(char * input) {

    int numCommands = 3;
    int trigger = 0;
    char * listCommands[numCommands];

    listCommands[0] = "printid";
    listCommands[1] = "exit";
    listCommands[2] = "greet";

    // iterate through list and compare with user input to trigger correct command
    for (int i = 0; i < numCommands; i++) {
        if (strcmp(input, listCommands[i]) == 0) {
            trigger = i+1;
            break;
        }
    }

    switch (trigger) {

        case 1: printf("%d\n", getpid());

        case 2: exit(0);

        case 3: printf("Hello\n");

        default: break;
    }
}

// function to match user input with command and execute as new process
void forkCommands(char * input) {

    int numCommands = 5;
    int trigger = 0;
    char * listCommands[numCommands];
    char * path;
    char * argv[2];

    listCommands[0] = "ls";
    listCommands[1] = "pwd";
    listCommands[2] = "ps";
    listCommands[3] = "date";
    listCommands[4] = "lscpu";

    // iterate through list and compare with user input to trigger correct command
    for (int i = 0; i < numCommands; i++) {
        if (strcmp(input, listCommands[i]) == 0) {
            trigger = i+1;
            break;
        }
    }

    switch (trigger) {

        case 1:
            path = "/bin/ls";
            argv[0] = path;
            argv[1] = NULL;
            execve( path, argv, NULL );

        case 2:
            path = "/bin/pwd";
            argv[0] = path;
            argv[1] = NULL;
            execve( path, argv, NULL );

        case 3:
            path = "/bin/ps";
            argv[0] = path;
            argv[1] = NULL;
            execve( path, argv, NULL );

        case 4:
            path = "/bin/date";
            argv[0] = path;
            argv[1] = NULL;
            execve( path, argv, NULL );

        case 5:
            path = "/bin/lscpu";
            argv[0] = path;
            argv[1] = NULL;
            execve( path, argv, NULL );

        default: break;
    }
}


int main() {

    int child;

    while (1) {

        printf("lab1> ");

        char command[MAX];
        scanf("%s", command);

        printf("Parent Process %d\n", getpid());

        // check if command entered is already built in
        if ( (strcmp(command, "printid") == 0) || (strcmp(command, "exit") == 0) || (strcmp(command, "greet") == 0) ) {
            builtIn(command);
            continue;
        }

        else {

            pid_t pid = fork();

            // handle if fork failed
            if ( pid < 0 ) {
                printf("Error with fork");
                exit(0);
            }

            // execute command in new process
            else if (pid == 0) {
                printf("Child process %d will execute the command %s\n", getpid(), command);
                forkCommands(command);
            }

            // wait for child process to complete then exit to prevent zombie
            else {
                wait(&child);
            }
        }

    }

}
