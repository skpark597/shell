#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  setbuf(stdout, NULL);

  // Wait for user input
  char input[100];

  while (1) {
    printf("$ ");
    if (fgets(input, sizeof(input), stdin) == NULL) break;

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "exit") == 0) break;

    if (strlen(input) > 0) {
      printf("%s: command not found\n", input);
    }
  }

  return 0;
}
