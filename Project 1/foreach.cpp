#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[]) {
  //https://stackoverflow.com/questions/52467531/using-getopt-in-c-to-handle-arguments
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
        cout << "Usage: ./foreach [-p] [-n NUM] [ARGS]... PROG" << endl;
        break;
    }
}