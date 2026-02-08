#include "builtins.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "context.h"
#include "utils.h"

Builtin builtins[] = {
    {"echo", do_echo}, {"exit", do_exit}, {"type", do_type},
    {"pwd", do_pwd},   {"cd", do_cd},     {NULL, NULL},
};

int find_builtin_idx(char* cmd) {
  if (!cmd) return -1;

  for (int i = 0; builtins[i].name != NULL; ++i) {
    if (strcmp(cmd, builtins[i].name) == 0) return i;
  }

  return -1;
}

int execute_builtin(char** args) {
  if (!args || !args[0]) return 0;

  int idx = find_builtin_idx(args[0]);

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

  if (find_builtin_idx(cmd) != -1) {
    printf("%s is a shell builtin\n", cmd);
    return;
  }

  char* path = find_executable_path(g_ctx.paths, cmd);

  if (path) {
    printf("%s is %s\n", cmd, path);
  } else {
    printf("%s: not found\n", cmd);
  }
}

void do_pwd(char** args) {
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  } else {
    perror("getcwd() error");
  }
}

void do_cd(char** args) {
  if (!args[1]) return;

  if (chdir(args[1]) == -1) {
    fprintf(stderr, "cd: %s: No such file or directory\n", args[1]);
    g_ctx.last_exit_status = 1;
  } else {
    getcwd(g_ctx.cwd, sizeof(g_ctx.cwd));
    g_ctx.last_exit_status = 0;
  }
}