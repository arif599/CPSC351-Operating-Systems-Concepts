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

//Store parameters and programs to run 
vector<char *> args; 
pid_t rc;
pid_t parent_wait; 

for(int i = 1; i<argc; i++){

  args.push_back(strdup(argv[i]));
}


for(int j = 1; j<=argc-2; j++ ){

  rc = fork();


  if(rc == 0){

    execvp(args.back(), args.data());
    //execlp(args.back(), args[j], NULL); //program to run is last arg
  
  } else{

      if(rc < 0){return EXIT_FAILURE;}


      else {parent_wait = wait(NULL);}
    }
}


  //https://stackoverflow.com/questions/52467531/using-getopt-in-c-to-handle-arguments
   /* switch(getopt(argc, argv, "pn:")){
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
        //cout << "Usage: ./foreach [-p] [-n NUM] [ARGS]... PROG" << endl;
        break;
    }*/



return EXIT_SUCCESS;

}
