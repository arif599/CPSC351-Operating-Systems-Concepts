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

int main(int argc, char *argv[]) {

//Store PROG to run by fetching last argument
vector<char *> args;
args.push_back(strdup(argv[argc-1]));

pid_t pid;    //Will be used to create child process 
pid_t wc;     //Used for waiting on child process  


  //Use getopt() for optional parameters 
  switch(getopt(argc, argv, "pn:")){

      case 'p':   //Argument for parallel execution 

        for(int i=2; i<argc-1; i++){ //Loop will start on argument after [-p]
        
          args.push_back(strdup(argv[i]));  //Store argument starting after [-p]

          pid = fork(); //create child process 

          if(pid < 0){
              cerr << "Fork failed\n";
              exit(EXIT_FAILURE);

          }else if(pid == 0) {  //Child process 
            
            //Exec current argument 
            execvp(args[0], args.data()); 

          }else { //Parent process 
          //Parent should not wait for child to finish

          args.pop_back();  //Remove current argument so we can run next argument 
          }
        }
        break;

    
    case 'n':  //Argument for to run program N times 
  
        for(int i=3; i<argc-1; i++){  //Main loop used to retrieve arguments after [-n NUM] 
          for(int j=0; j<stoi(optarg); j++){ //loop for number of times to run program
            
            args.push_back(strdup(argv[i]));
            pid = fork();

            if(pid < 0){  
              exit(EXIT_FAILURE);

            }else if(pid == 0){
              
              execvp(args[0], args.data()); 

            }else{  //In parent; wait for child to finish 

              int wc = wait(NULL);
              args.pop_back();
            }
          }  
        }
        break;

       
    default :   //No optional arguments given 

      if(argc == 1){  //If no arguments given at all 

        cout << "Usage: ./foreach [-p] [-n NUM] [ARGS]... PROG" << endl;
      }else{
 
        for(int i=1; i<argc-1; i++){ //Loop used to exec first given argument 

          args.push_back(strdup(argv[i]));
          pid = fork();

          if(pid < 0){
            cerr << "Fork failed\n";
            exit(EXIT_FAILURE);

          }else if(pid == 0){   //Child process 

              execvp(args[0], args.data()); 

          }else { //Parent process; wait for child to finish 

            int wc = wait(NULL);
            args.pop_back();
            }
        }
      }
    }
   

   return EXIT_SUCCESS;
   
}
