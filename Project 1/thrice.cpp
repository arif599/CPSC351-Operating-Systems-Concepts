#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
  
// Driver code
int main(int argc, char *argv[]){

	// if no arguments were passed
	if(argc == 1){
		cerr << "Usage: ./thrice PROG [ARGS]..." << endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < 3; i++){
		// fork a child process
      	int pid = fork();

		// if process is child
		if(pid == 0){
			if(argv[1] == "echo"){
			cout << argv[2] << endl;
			}else{
			cout << argv[1] << endl;
			}
			// to exit the child process
			return NULL;
		}else{
			// wait for the child process to finish
			wait(&pid);
		}
    }
}