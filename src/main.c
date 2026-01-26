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

    char* args_array[64];
    char* token = strtok(input, " ");
    int i = 0;

    if (token == NULL) continue;

    while (token != NULL && i < 63) {
      args_array[i++] = token;
      token = strtok(NULL, " ");
    }
    args_array[i] = NULL;

    char* cmd = args_array[0];
    int is_builtin_executed = 0;

    for (int i = 0; i < 4; i++) {
      if (strcmp(cmd, builtins[i].name) == 0) {
        builtins[i].func(args_array);
        is_builtin_executed = 1;
        break;
      }
    }

    if (!is_builtin_executed && cmd != NULL) {
      int result = execute_command(args_array);
      if (result == -1) printf("%s: command not found\n", cmd);
    }
  }

  return 0;
}
