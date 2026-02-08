#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "context.h"
#include "extern.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  setbuf(stdout, NULL);
  char input[100];

  init_context();

  while (g_ctx.is_running) {
    printf("$ ");

    if (fgets(input, sizeof(input), stdin) == NULL) break;
    input[strcspn(input, "\n")] = '\0';

    char** args = split_tokens(input, " ");

    if (!args || !args[0]) {
      free_tokens(args);
      continue;
    }

    if (!execute_builtin(args)) {
      if (!execute_extern(args)) {
        printf("%s: command not found\n", args[0]);
      }
    }

    free_tokens(args);
  }

  cleanup_context();

  return g_ctx.last_exit_status;
}
