from ast import Break
from contextlib import nullcontext
import os, sys, time

os.system('cls' if os.name == 'nt' else 'clear')    ## if Windows cls (NT), else clear (Unix)

prompt = "Input>"
n = len(sys.argv)

## Checks for 2nd argument for custom prompt
if (len(sys.argv) == 2):
    if (sys.argv[1] == "p"):
        prompt = input("Please name prompt: ")
    else:
        print("Invalid argument!")
        sys.exit()
elif (len(sys.argv) > 2):
    print("Too many arguments!")
    sys.exit()

os.system('cls' if os.name == 'nt' else 'clear')    ## if Windows cls (NT), else clear (Unix)

print("Command List:\nhelp - I forgot what all I can do")

## Help list
def print_Help():
    print("exit - Exits program")
    print("pid - Prints out child process ID")
    print("ppid - Prints out Parent process ID")
    print("cd - Changes directory")
    print("pwd - Prints out current working directory")
    print("sleep - Cause system to sleep for <num> seconds\n")
print_Help()

## Main program prompting user for selection
def main_loop():
    while(True):
        user_Command = input(prompt)
        if (user_Command == "help"):    ## Print help list
            print_Help()
        elif (user_Command == "pid"):   ## Print Parent/Child pid
            pid = os.fork()
            if (pid > 0):
                print("Parent process ID: " + str(os.getpid()))
            else:
                print("Child process ID: " + str(os.getpid()))
                sys.exit()
            time.sleep(0.1)
        elif (user_Command == "ppid"):  ## Print Parent/Child ppid
            print("Parent process ID: " + str(os.getppid()))
            print("Child process ID: " + str(os.getpid()))
        elif (user_Command == "pwd"):   ## Print working directory
            print("Current working directory: " + os.getcwd())
        elif (user_Command == "cd"):    ## Change working directory
            change_Dir = input("Change directory to: ")
            try:
                os.chdir(change_Dir)
            except:
                print("Directory does not exist!")
        elif (user_Command == "sleep"): ## Sleep system for user defined amount of time
            try:
                sleep_Num = int(input("How many seconds: "))
                print("Sleeping for " + str(sleep_Num) + " seconds...")
                time.sleep(int(sleep_Num))
            except:
                print("Not a valid input!")
        elif (user_Command == "exit"):  ## Exit program
            break
        else:
            print("Invalid input")      ## Input not valid

if __name__ == '__main__':
    main_loop()