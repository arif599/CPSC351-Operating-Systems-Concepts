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

   switch(getopt(argc, argv, "pn:")){
      case 'p':{
        // todo
      }
    case 'n':{
      // todo, might be incorect 
      for(int j=3; j<argc; j++){
        for(int i=0; i<stoi(optarg); i++){
              int pid = fork();
              if(pid == 0){
                cout << argv[j] << endl;
                return NULL;
              }else{
                wait(&pid);
              }
            }
          }
        break;
    }
    default :
      if(argc == 1){
        cout << "Usage: ./foreach [-p] [-n NUM] [ARGS]... PROG" << endl;

      }else{
      //cout << argv[argc-1] << endl;
        //arguments to execute 
        vector<char *> args;
        cout << "Program: " << argv[argc-1] << endl;
        args.push_back(strdup(argv[argc-1]));
        for(int i=1; i<argc-1; i++){
          cout << "arguments: " << argv[i] << endl;
          args.push_back(strdup(argv[i]));
        }

        auto pid = fork();

        if(pid < 0){
            //cout << "fork failed\n";
            exit(EXIT_FAILURE);
            
        }  else if(pid == 0){
              execvp(args[0], args.data()); 
              // for(int i=0; i < args.size()-1; i++){
              //   execvp(args[i+1], args.data()); 
              // }
                

        }else { //Parent waits for child process to finish

            int wc = wait(NULL);
            
            }
        break;
      }
    }



return EXIT_SUCCESS;

}