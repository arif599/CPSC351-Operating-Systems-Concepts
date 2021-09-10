#include<iostream> 
#include<unistd.h>
#include<string>
#include<stdlib.h>

using namespace std;



int main(int argc, char * argv[]){


int rc = fork();

if(rc < 0){
	cout << "fork failed\n";
	exit(1);
}


else if(rc == 0){
	char * foo;
	foo = new char[3];
	foo[0] = *strdup(argv[1]);
	foo[1] = *strdup("thrice.cpp");
	foo[2] = NULL;

	for(int i=0; i<2;i++){

		execvp(foo[0],foo);

		}
	}

else {
	cout << "Main process";

	}

return 0;

}
