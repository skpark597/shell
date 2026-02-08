#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "executor.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  setbuf(stdout, NULL);
  char input[100];

  while (1) {
    printf("$ ");

    if (fgets(input, sizeof(input), stdin) == NULL) break;
    input[strcspn(input, "\n")] = '\0';

    char** args = split_tokens(input, " ");
    char* cmd = args[0];

    int is_builtin_executed = 0;

    for (int i = 0; i < 4; i++) {
      if (strcmp(cmd, builtins[i].name) == 0) {
        builtins[i].func(args);
        is_builtin_executed = 1;
        break;
      }
    }

    if (!is_builtin_executed && cmd != NULL) {
      int result = execute_command(args);
      if (result == -1) printf("%s: command not found\n", cmd);
    }
  }

  return 0;
}
