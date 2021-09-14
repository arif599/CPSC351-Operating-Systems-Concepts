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

  // arguments to execute
  if (argc == 1) {
    cerr << "Usage: ./thrice PROG [ARGS]..." << endl;
    exit(EXIT_FAILURE);
  }

  // arguments to execute
  vector<char *> args;
  if (strcmp(argv[1], "echo") == 0) {
    args.push_back(strdup(argv[1]));
    for (int i = 2; i < argc; i++) {
      args.push_back(strdup(argv[i]));
    }
  } else {
    args.push_back(strdup(argv[1]));
    args.push_back(NULL);
  }

  // Create 3 new child processes
  pid_t pid = fork();
  pid_t pid_2 = fork();

  if (pid < 0) {
    // cout << "fork failed\n";
    exit(EXIT_FAILURE);

  } else if (pid == 0) {

    execvp(args[0], args.data());

  } else if (pid_2 == 0) {

    execvp(args[0], args.data());

  } else { // Parent waits for child process to finish

    int wc = wait(NULL);
  }

  return EXIT_SUCCESS;
}
