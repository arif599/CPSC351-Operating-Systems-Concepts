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
using std::vector;

int main(int argc, char *argv[]) {

  pid_t pid;
  pid_t c;
  // arguments to execute
  if (argc == 1) {
    cerr << "Usage: ./thrice PROG [ARGS]..." << endl;
    exit(EXIT_FAILURE);
  }

  // arguments to execute
  vector<char *> args;

  // Check if echo command
  if (strcmp(argv[1], "echo") == 0) {
    args.push_back(strdup(argv[1]));
    for (int i = 2; i < argc; i++) {
      args.push_back(strdup(argv[i]));
    }
  } else {
    args.push_back(strdup(argv[1]));
    args.push_back(NULL);
  }

  for (int i = 0; i <= 2; i++) {
    // loop for our child process to execute

    pid = fork();

    if (pid == 0) { // child process

      execvp(args[0], args.data());

    } else {

      if (pid < 0) {
        cerr << "fork failed\n";
        return EXIT_FAILURE;

      } else { // Parent process waiting for child to finish

        c = wait(NULL);
      }
    }
  }
  return EXIT_SUCCESS;
}
