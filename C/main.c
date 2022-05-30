#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

void user_input();
void main_loop();
void builtin_commands(char *args0, char *args1);
pid_t pidSplit = -1, wpid;
char *prompt = NULL;

/*
* Main function, defines optcode and sets prompt accordingly
*/
int main(int argc, char* argv[]){
    int arg;

	while((arg = getopt(argc, argv, "p:")) != -1){  // Check for conditions on command line during execution 
		switch(arg){
		case 'p':                    // If -p is found, set prompt as given optarg as the user defines
			prompt = optarg;
			break;
		default:
			exit(1);                 // If nothing, exit and run without modification
		}   
    }
    if (prompt == NULL)              // If prompt isn't set by user, give default and clear screen
            prompt = "Input> ";
            system("clear");
            printf("Command List:\nHelp - I forgot what all I can do\n");
            printf("exit - Exits program\n");
            printf("pid - Prints out child process ID\n");
            printf("ppid - Prints out Parent process ID\n");
            printf("cd - Changes directory\n");
            printf("pwd - Prints out current working directory\n");
            printf("sleep <num> - Cause system to sleep for <num> seconds\n\n");
            main_loop(prompt);

        return 0;
}

/*
* Main program loop
*/
void main_loop(char prompt[]){
        for(;;){                    // Run infinite loop, printing prompt and calling user_input() function
            printf("%s", prompt);
            user_input();
    }
}