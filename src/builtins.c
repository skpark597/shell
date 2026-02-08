#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

Builtin builtins[] = {
    {"echo", do_echo}, {"exit", do_exit}, {"type", do_type}, {"pwd", do_pwd}};

void do_echo(char** args) {
  if (args != NULL) printf("%s\n", join_args(args));
}

void do_exit(char** args) { exit(0); }

void do_type(char** args) {
  if (args == NULL) return;
  char* cmd = args[1];

  for (int i = 0; i < 4; i++) {
    if (strcmp(cmd, builtins[i].name) == 0) {
      printf("%s is a shell builtin\n", cmd);
      return;
    }
  }

  char** dirs = split_tokens(getenv("PATH"), ":");
  char* found_path = find_executable_path(cmd, dirs);

  if (found_path) {
    printf("%s is %s\n", cmd, found_path);
  } else {
    printf("%s: not found\n", cmd);
  }

  free_tokens(dirs);
}

void do_pwd(char** args) {
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  } else {
    perror("getcwd() error");
  }
}