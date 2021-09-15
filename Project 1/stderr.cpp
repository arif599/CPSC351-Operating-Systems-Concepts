#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  
  // executing command
  vector<char *> args;
  if (strcmp(argv[2], "echo") == 0) {
    args.push_back(strdup(argv[1]));
    for (int i = 2; i < argc; i++) {
      args.push_back(strdup(argv[i]));
    }
  } else {
    args.push_back(strdup(argv[2]));
    args.push_back(NULL);
  }

  pid_t pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }else if(pid == 0) {
    close(STDERR_FILENO);
    open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    execvp(args[0], args.data());
  }else{ 
    int wc = wait(NULL);
  }

  return EXIT_SUCCESS;

  
}