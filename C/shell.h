#ifndef SHELL_H
#define SHELL_H

/*
* variables shared between command.c and main.c
*/

extern int splitFlag;
extern pid_t cpid, wpid, pidSplit;
extern char *prompt;

#endif