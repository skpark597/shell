#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "context.h"
#include "utils.h"

int execute_extern(char** args) {
  if (!args || !args[0] || !g_ctx.paths) return 0;

  char* path = find_executable_path(g_ctx.paths, args[0]);
  if (!path) return 0;

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    free(path);
    return -1;
  }

  if (pid == 0) {
    // child process
    if (execv(path, args) == -1) {
      perror("execv failed");
      free(path);
      exit(1);
    }
  } else {
    // parent process
    int status;
    waitpid(pid, &status, 0);
    free(path);
  }

  return 1;
}