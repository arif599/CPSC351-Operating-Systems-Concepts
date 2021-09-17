
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
  vector<char *> args;    //Used for storing arguments
  pid_t pid;              //Used to create child processes
  pid_t wc;               //Used to wait for child process 


  if(argc == 3){

    //Store command to run 
    args.push_back(strdup(argv[2])); 
    args.push_back(NULL);
    pid = fork();

    if(pid < 0){
      cerr << "Fork failed\n";
      exit(EXIT_FAILURE);
    }

    else if(pid == 0) { //redirect output to file given in child process
      close(STDOUT_FILENO);
      open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
      execvp(args[0], args.data());
    }
    else{ 
      wc = wait(NULL); 
      execvp(args[0],args.data());
    }
  }

  else if(argc<3) {
    cerr << "Usage: ./stderr FILE PROG [ARGS]...\n";
    exit(EXIT_FAILURE);
  }
  
  else{
    
      if(strcmp(argv[argc-1],"-l") == 0){ //check for flags 
        pid = fork();

        if(pid < 0){
          cerr << "Fork failed.\n";
          exit(EXIT_FAILURE);
        }
        else if(pid == 0){
          
          //run remaining commands in child process  
          args.push_back(strdup(argv[argc-2]));
          args.push_back(strdup(argv[argc-1]));
          args.push_back(NULL);
          execvp(args[0], args.data());
        }

        else{ //redirect output of command to given file in parent process

          wc = wait(NULL);
          args.push_back(strdup(argv[2]));
          for(int i = 3; i<argc; i++){
            args.push_back(strdup(argv[i]));
          }
          close(STDOUT_FILENO);
          open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
          execvp(args[0], args.data());
        }
      }

      
      else{ //when no flags are indicated

        pid = fork();

        if(pid < 0){
          cerr << "Fork failed\n";
          exit(EXIT_FAILURE);
        }
        else if(pid == 0){  //run given commands in child process

          args.push_back(strdup(argv[argc-1]));
          args.push_back(NULL);
          execvp(args[0],args.data());
        }

        else { //redirect output of command to given file in parent process

          wc = wait(NULL);
    
          for(int i = 2; i < argc; i++){
            args.push_back(strdup(argv[i]));

          }
          close(STDOUT_FILENO);
          open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

          execvp(args[0],args.data());
        }

      }

    }

    return EXIT_SUCCESS;
}
