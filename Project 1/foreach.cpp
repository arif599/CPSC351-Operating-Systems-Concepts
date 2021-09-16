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


  vector<char *> args;

   switch(getopt(argc, argv, "pn:")){
      case 'p':
        //arguments to execute 
        //cout << "Program: " << argv[argc-1] << endl;
        args.push_back(strdup(argv[argc-1]));
        for(int i=2; i<argc-1; i++){
          //cout << "arguments: " << argv[i] << endl;
          args.push_back(strdup(argv[i]));

          pid_t pid = fork();
          if(pid < 0){
              //cout << "fork failed\n";
              exit(EXIT_FAILURE);
          }else if(pid == 0){
            //cout << "Child program: " << args[0] << endl;
            execvp(args[0], args.data()); 
        }else{ //Parent does not wait for child process to finish
            args.pop_back();
          }
        
        }
        break;
    
    case 'n':
  
        //cout << "Program: " << argv[argc-1] << endl;
        args.push_back(strdup(argv[argc-1]));
        for(int i=3; i<argc-1; i++){
          for(int j=0; j<stoi(optarg); j++){
            //cout << "arguments: " << argv[i] << endl;
            args.push_back(strdup(argv[i]));

            pid_t pid = fork();
            if(pid < 0){
                //cout << "fork failed\n";
                exit(EXIT_FAILURE);
            }else if(pid == 0){
              //cout << "Child program: " << args[0] << endl;
              execvp(args[0], args.data()); 
            }else{ //Parent does not wait for child process to finish
              int wc = wait(NULL);
              args.pop_back();
            }
          }  
        }
        break;
    default :
      if(argc == 1){
        cout << "Usage: ./foreach [-p] [-n NUM] [ARGS]... PROG" << endl;
      }else{

        //arguments to execute 
        //cout << "Program: " << argv[argc-1] << endl;
        args.push_back(strdup(argv[argc-1]));
        for(int i=1; i<argc-1; i++){
          //cout << "arguments: " << argv[i] << endl;
          args.push_back(strdup(argv[i]));

          pid_t pid = fork();
          if(pid < 0){
              exit(EXIT_FAILURE);
          }else if(pid == 0){
              execvp(args[0], args.data()); 
          }else { //Parent waits for child process to finish
            int wc = wait(NULL);
            args.pop_back();
            }
        }
      }
      break;
    }
   

   return EXIT_SUCCESS;
   
}
