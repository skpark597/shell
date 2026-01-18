#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"

int main(int argc, char* argv[]) {
  setbuf(stdout, NULL);
  char input[100];

  while (1) {
    printf("$ ");

    if (fgets(input, sizeof(input), stdin) == NULL) break;
    input[strcspn(input, "\n")] = '\0';

    char* ptr = strtok(input, " ");
    char* args = strtok(NULL, "");

    int handled = 0;

    for (int i = 0; i < 3; i++) {
      if (strcmp(ptr, builtins[i].name) == 0) {
        builtins[i].func(args);
        handled = 1;
        break;
      }
    }

    if (!handled && ptr != NULL) printf("%s: command not found\n", input);
  }

  return 0;
}