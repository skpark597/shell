#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

Builtin builtins[] = {{"echo", do_echo}, {"exit", do_exit}, {"type", do_type}};

void do_echo(char* cmd) {
  if (cmd != NULL) printf("%s\n", cmd);
}

void do_exit(char* cmd) { exit(0); }

void do_type(char* cmd) {
  if (cmd == NULL) return;

  for (int i = 0; i < 3; i++) {
    if (strcmp(cmd, builtins[i].name) == 0) {
      printf("%s is a shell builtin\n", cmd);
      return;
    }
  }

  char* path_env = getenv("PATH");
  char** dirs = split_path(path_env);
  int i = 0;
  int found = 0;

  if (dirs) {
    char* dir = dirs[0];

    while (dir) {
      char* full_path = join_path(dir, cmd);

      if (access(full_path, X_OK) == 0) {
        printf("%s is %s\n", cmd, full_path);
        found = 1;
        break;
      }

      i++;
      dir = dirs[i];
    }
  }

  free_path_array(dirs);
  if (found == 0) printf("%s: not found\n", cmd);
}