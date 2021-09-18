#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include<iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;
using std::vector;


int main(int argc, char *argv[])
{

  if(argc < 3){
    cerr << "Usage: ./stderr FILE PROG [ARGS]...\n";
    exit(EXIT_FAILURE);
  }

  vector<char *> args;    //Used for storing arguments
  int pid = fork();

  if(pid < 0){
  cerr << "Fork failed.\n";
  exit(EXIT_FAILURE);

  }else if(pid == 0){ 
    if(argc >= 3){    //Store all arguments if 2 or more given 

      for(int i = 2; i < argc; i++){    //Store all arguments given after txt file
        args.push_back(strdup(argv[i]));
      }

    }else{    //if less than 2 arguments given 

      args.push_back(strdup(argv[2]));  //Store the command to run 
      args.push_back(NULL);
    }

    //Redirect output of the standard error stream of the argument given after txt file
    close(STDERR_FILENO);
    open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    execvp(args[0],args.data());  //execute the remaining commands 

  }else{    //In parent process, wait for child to finish
    int rc_wait = wait(NULL);
  }

    return EXIT_SUCCESS;
}
