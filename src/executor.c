#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"

int execute_command(char** args) {
  char** dirs = split_path(getenv("PATH"));
  char* found_path = NULL;
  char* cmd = args[0];

  if (!dirs) return -1;

  for (int i = 0; dirs[i] != NULL; i++) {
    char* full_path = join_path(dirs[i], cmd);

    if (access(full_path, X_OK) == 0) {
      found_path = full_path;
      break;
    }
  }

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

    free_path_array(dirs);
    return 0;
  }

  free_path_array(dirs);
  return -1;
}