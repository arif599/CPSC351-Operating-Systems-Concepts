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

	int pid, pid1, pid2;
	pid = fork();
	if(pid == 0){
		// child 1 gets printed first
		cout << argv[1] << endl;
	}
	else{
		wait(NULL);
		pid1 = fork();
		if (pid1 == 0) {
			// child 2 gets printed second
			cout << argv[1] << endl;
		}
		else {
			wait(NULL);
			pid2 = fork();
			if (pid2 == 0) {
				// child 3 gets printed third
				cout << argv[1] << endl;
			}
		}
	}
}