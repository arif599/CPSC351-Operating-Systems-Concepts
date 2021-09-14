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

using std::vector;


int main(int argc, char * argv[]){

//arguments to execute 
vector<char *> args;
args.push_back(strdup(argv[1]));
args.push_back(NULL);

//Create 3 new child processes 
auto pid = fork();
auto pid_2 = fork();

if(pid < 0){
    //cout << "fork failed\n";
    exit(EXIT_FAILURE);
    
}  else if(pid == 0){
        
        execvp(args[0], args.data()); 

}  else if(pid_2 == 0){
    
        execvp(args[0], args.data());

}  else { //Parent waits for child process to finish

    int wc = wait(NULL);
    
    }

return EXIT_SUCCESS;

}

