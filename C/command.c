#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_LINE 80
int splitFlag = 0, status;
pid_t cpid;

void main_loop();
void exit_status(int cpid, int status, char *args0);

/*
* Builtin Commands functions
*/
void builtin_commands(char *args0, char *args1){

    if (strcmp(args0, "exit" ) == 0)            // Exit shell
        exit(0);
    else if (strcmp(args0, "pid") == 0)         // Print child process ID
        printf("Process ID: %d\n",getpid());
    else if (strcmp(args0, "ppid") == 0)        // Print parent process ID
        printf("Parent process ID: %d\n",getppid());
    else if (strcmp(args0, "cd") == 0){         // Change directory
        if (args1 == NULL){                     // Change directory to /home
            char cwd[1024];
            chdir("/home");
            getcwd(cwd, sizeof(cwd));
            printf("Current working dir: %s\n", cwd);
        }
        else if (chdir (args1) != 0)            // Error in cd command
            perror("cd failure");
        else{                                   // Change directory to user stated directory
            char cwd[1024];
            chdir(args1);
            getcwd(cwd, sizeof(cwd));
            printf("Current working dir: %s\n", cwd);
        }
    }
    else if (strcmp(args0, "pwd") == 0){        // Print current working directory
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("Current working dir: %s\n", cwd);
    }
    else if (strcmp(args0, "sleep") == 0){      // Sleep for user allocated amount of time
        if (atoi(args1) <= 0)
            printf("Command failed, please type a whole integer larger than 0\n");
        else{
        printf("Sleeping for %d second(s)\n", atoi(args1));
        sleep(atoi(args1));
        }
   }
    else if (strcmp(args0, "help") == 0){         // Print print list of commands
        printf("exit - Exits program\n");
        printf("pid - Prints out child process ID\n");
        printf("ppid - Prints out Parent process ID\n");
        printf("cd - Changes directory\n");
        printf("pwd - Prints out current working directory\n");
        printf("sleep <num> - Cause system to sleep for <num> seconds\n\n");
        }
    else                                       // Throw error stating that command given is not found
        printf("Cannot exec %s: YOU CONFUSE ME WITH YOUR INVALID COMMANDS!\n", args0);
    
    if(pidSplit == 0)
        exit_status(getpid(), status, args0);
 }


/*
* User input breakdown, also catches "&" suffix and runs excevp
*/
void user_input(){
char text[MAX_LINE], *args[MAX_LINE/2 + 1];
int pid, flag = 0;

fgets(text, MAX_LINE, stdin);                   // Gets command line input to the length of MAX_LINE and stores it in text
    if(text[strlen(text)-2] == '&'){            // Check if last char is & and set splitFlag accordingly
        switch (pidSplit = fork()){             // Fork in the event of &
            case 0:
                printf("[%d] \n", getpid());
                cpid = wait(NULL);              // Wait for child process to catch up
                main_loop(prompt);              // Run child process, terminate when finished
                exit(1);
                break;
            default:
                while ((wpid = wait(&status)) > 0); // Halt parent process while child is running
                break;
            case -1:
                perror("fork");                 // Throw error on bad fork
                exit(1);
            }
    }
    text[strlen(text) -1 ] = '\0';              // Sets null marker at end of string
        args[0] = strtok(text, " ");            // Cuts off after the first space and stores the first argument into arg[0]
        int i = 0;
        while (args[i] != NULL)
            args[++i] = strtok(NULL, " ");      // Store the remaining arguments into arg[1], arg[2], ..., arg[n]
        switch (pid = vfork()){                 // Using vfork() so parent and child share address space
            case 0:
                if (strlen(text) == 0)          // Check if char[] is empty and skip if true
                    exit(1);
                else if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "pwd") == 0 || strcmp(args[0], "sleep")   == 0){
                    flag = 1;                   // If cd, pwd, or sleep is called, run it through builtin_commands instead of execvp
                    exit(1);                    // Kill child prosses
                }
                else{
                    printf("[%d] \n", getpid());
                    cpid = wait(NULL);
                    execvp(args[0], args);          // Run execvp if applicable, otherwise set flag
                    flag = 1;
                    exit(1);                        // Kill child process
                }
            default:
                    cpid = wait(NULL);                   
                    if (flag == 1){
                        builtin_commands(args[0], args[1]);  // Send 'text' to user_command if flag is set (execvp did not execute)
                }
                break;
            case -1:
                perror("fork");                       // Print fork error
                exit(1);
        }
}

/*
* Exit status, cpid, and process name listing
*/
void exit_status(int cpid, int status, char *args0){
            wait(&status);
        if(WIFEXITED(status))
            printf("[%d] %s Exit %d\n", cpid, args0, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("[%d] %s Exit %d\n", cpid, args0, WTERMSIG(status));
}