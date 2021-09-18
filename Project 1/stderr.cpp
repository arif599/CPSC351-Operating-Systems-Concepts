#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include<iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;
using std::vector;


int main(int argc, char *argv[])
{

  if(argc < 3){
    cerr << "Usage: ./stderr FILE PROG [ARGS]...\n";
    exit(EXIT_FAILURE);
  }
  vector<char *> args;    //Used for storing arguments
  int pid = fork();
  if(pid < 0){
  cerr << "Fork failed.\n";
  exit(EXIT_FAILURE);
}else if(pid == 0){
    if(argc >= 3){
      for(int i = 2; i < argc; i++){
        args.push_back(strdup(argv[i]));
      }

    }else{
      args.push_back(strdup(argv[2]));
      args.push_back(NULL);
    }

    close(STDERR_FILENO);
    open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    execvp(args[0],args.data());
  }else{
    int rc_wait = wait(NULL);
  }

    return EXIT_SUCCESS;
}
