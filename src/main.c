#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "extern.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  setbuf(stdout, NULL);
  char input[100];

  while (1) {
    printf("$ ");

    if (fgets(input, sizeof(input), stdin) == NULL) break;
    input[strcspn(input, "\n")] = '\0';

    char** args = split_tokens(input, " ");

    if (!args || !args[0]) {
      free_tokens(args);
      continue;
    }

    if (execute_builtin(args)) {
      free_tokens(args);
      continue;
    }

    if (!execute_extern(args)) {
      printf("%s: command not found\n", args[0]);
    }

    free_tokens(args);
  }

  return 0;
}
