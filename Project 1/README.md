# Assignment 1
---
## Group Members
Arifulla Shaik (arifullashaik@csu.fullerton.edu)

Angarag Gansukh (angaraggansukh@csu.fullerton.edu)

Lea Albano (leaalbano@csu.fullerton.edu)

---
## thrice.cpp
**Description:** runs a given command three times <br />
**Usage:** `Usage: ./thrice PROG [ARGS]...` <br />
**Summary:** We first started with thrice.cpp. We first check how many arguments were given to make the necessary outputs needed. If there was no arguments provided then we display an error message. If there was more than 2 arguments, we need to use a for-loop that will loop based on the number of arguments to execute the command on. If there are only 2 arguments we know to only execute the first command, requiring us to only store that command and terminate the vector with a null. Then, we proceed to another for-loop that will loop 3 times since we want to run the given command 3 times in a child process. The for-loop allows us to run the command consecutively, where the next child process will run after the previous child process completes. Using a vector that stored all our arguments, we are able to then run execvp() using that vector.

## foreach.cpp
**Description:** repeats a command with a list of arguments <br />
**Usage:** `./foreach [-p] [-n NUM] [ARGS]... PROG` <br />
**Summary:** For foreach, we also use a vector in order to utilize the exec command. First, we use a switch statement along with getopt() to check if optional arguments were given. For the -p argument case, we run a for-loop that will loop based on the number of arguments and in each loop will execute the command. However, since we want to execute the arguments separately, we store the arguments one by one, where we execute that argument and then pop it in the parent process so we can execute the next argument. The parent process also does not call wait() so we can run the processes in parallel. For the -n argument, we start off with 2 nested for-loops. The main loop will be used to keep track of which argument we are on and the inner loop will execute the argument based on the number provided by optarg(). For the case when there are no optional arguments, we are doing the same thing as the -p case, but the parent will wait() on the child. 

## stderr.cpp:
**Descrption:** runs a command and saves the contents of its standard error stream to a file <br />
**Usage:** `Usage: ./stderr FILE PROG [ARGS]...` <br />
**Summary:** For stderr, we check if there's less than 1 argument given then we will display an error message. If 2 or more arguments are given, we start storing the arguments given after the txt file to execute. We will then execute any extra arguments given and then redirect the standard error stream of the command given after the txt file. 
