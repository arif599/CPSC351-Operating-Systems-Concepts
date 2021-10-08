#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
using namespace std;
using std::vector;

int main(int argc, char * argv[]){
	// if no arguments were passed
	if(argc == 1){
		cerr << "Usage: ./thrice PROG [ARGS]..." << endl;
		exit(EXIT_FAILURE);
	}

	//arguments to execute 
	vector<char *> args;
	if(strcmp(argv[1], "echo") == 0){
		args.push_back(strdup(argv[1]));
		for(int i=2; i<argc; i++){
			args.push_back(strdup(argv[i]));
		}
	}else{
		args.push_back(strdup(argv[1]));
		args.push_back(NULL);
	}

	//Create 3 new child processes 
	auto pid = fork();
	auto pid_2 = fork();
	if(pid < 0){
		exit(EXIT_FAILURE);
	}else if(pid == 0){ 
		execvp(args[0], args.data()); 
	}else if(pid_2 == 0){
		execvp(args[0], args.data());
	}else{ 
		//Parent waits for child process to finish
		int wc = wait(NULL);
	}

	return EXIT_SUCCESS;

<<<<<<< HEAD
=======

pid_t pid;              //Will be used to create our child process 
pid_t wc;              //Used for wait() to wait for child process 
vector<char *> args;  //Used for to store arguments 

  //If no arguments given 
if (argc == 1) {
  cerr << "Usage: ./thrice PROG [ARGS]..." << endl;
  exit(EXIT_FAILURE);
  }
 

  // if a command has multiple arguments
  if(argc > 2){
    args.push_back(strdup(argv[1]));  //Store command to exec 

    for (int i = 2; i < argc; i++) { //Loop for amount of arguments given

      //Store arguments 
      args.push_back(strdup(argv[i])); 
    }

  }else { // if command has no argument

    args.push_back(strdup(argv[1])); //Store first command to run 
    args.push_back(NULL);
  }

 

  for (int i = 0; i <= 2; i++) {  //Loop 3 times to exec command 3 times

    pid = fork();

    if (pid == 0) {    //child process

      //Exec given arguments in child process
      execvp(args[0], args.data());

    } else if (pid < 0) {
        cerr << "fork failed\n";
        return EXIT_FAILURE;

    } else {    //Parent process waiting for child to finish

        wc = wait(NULL);
      }
  
  }
  return EXIT_SUCCESS;
>>>>>>> 169898e482f46a2dcc61a77b33d7804f1f8f01b9
}
