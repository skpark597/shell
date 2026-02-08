#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"

int execute_extern(char** args) {
  if (!args || !args[0]) return 0;

  char** paths = split_tokens(getenv("PATH"), ":");
  char* cmd = args[0];

  if (!paths) return 0;

  char* found_path = find_executable_path(cmd, paths);

  if (found_path) {
    pid_t pid = fork();

    if (pid < 0) {
      perror("fork failed");
    } else if (pid == 0) {
      if (execvp(found_path, args) == -1) {
        perror("execvp failed");
        exit(1);
      }
    } else {
      int status;
      waitpid(pid, &status, 0);
    }

    free_tokens(paths);
    return 1;
  }

  free_tokens(paths);
  return 0;
}