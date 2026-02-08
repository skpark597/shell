#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

Builtin builtins[] = {
    {"echo", do_echo}, {"exit", do_exit}, {"type", do_type},
    {"pwd", do_pwd},   {NULL, NULL},
};

int get_builtin_idx(char* cmd) {
  if (!cmd) return -1;

  for (int i = 0; builtins[i].name != NULL; ++i) {
    if (strcmp(cmd, builtins[i].name) == 0) return i;
  }

  return -1;
}

int execute_builtin(char** args) {
  if (!args || !args[0]) return 0;

  int idx = get_builtin_idx(args[0]);

  if (idx != -1) {
    builtins[idx].func(args);
    return 1;
  }

  return 0;
}

void do_echo(char** args) {
  if (!args || !args[0]) return;

  for (int i = 1; args[i] != NULL; ++i) {
    printf("%s", args[i]);
    if (args[i + 1] != NULL) printf(" ");
  }

  printf("\n");
}

void do_exit(char** args) { exit(0); }

void do_type(char** args) {
  if (!args || !args[0] || !args[1]) return;

  char* cmd = args[1];
  int idx = get_builtin_idx(cmd);

  if (idx != -1) {
    printf("%s is a shell builtin\n", cmd);
    return;
  }

  char** paths = split_tokens(getenv("PATH"), ":");
  char* found_path = find_executable_path(cmd, paths);

  if (found_path) {
    printf("%s is %s\n", cmd, found_path);
  } else {
    printf("%s: not found\n", cmd);
  }

  free_tokens(paths);
}

void do_pwd(char** args) {
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  } else {
    perror("getcwd() error");
  }
}