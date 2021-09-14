#include<iostream>
#include<unistd.h>
#include<string>
#include<stdlib.h>
#include<sys/wait.h>
#include<vector>
#include <cstring>
#include <cassert>
#include<cstdlib>
#include<cstdio>
#include<fcntl.h>

using namespace std;


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

}