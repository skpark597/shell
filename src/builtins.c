#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Builtin builtins[] = {{"echo", do_echo}, {"exit", do_exit}, {"type", do_type}};

void do_echo(char* args) {
  if (args != NULL) printf("%s\n", args);
}

void do_exit(char* args) { exit(0); }

void do_type(char* args) {
  for (int i = 0; i < 3; i++) {
    if (strcmp(args, builtins[i].name) == 0) {
      printf("%s is a shell builtin\n", args);
      return;
    }
  }

  if (args != NULL) printf("%s: not found\n", args);
}