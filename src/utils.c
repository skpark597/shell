#define _POSIX_C_SOURCE 200809L
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count_tokens(const char* str, const char* delims) {
  if (str == NULL || *str == '\0') return 0;

  int count = 0, in_segment = 0;

  while (*str) {
    if (strchr(delims, *str) != NULL) {
      in_segment = 0;
    } else if (in_segment == 0) {
      in_segment = 1;
      count++;
    }

    str++;
  }

  return count;
}

char** split_tokens(const char* str, const char* delims) {
  if (str == NULL) return NULL;

  int count = count_tokens(str, delims);
  if (count == 0) return NULL;

  char** tokens = calloc(count + 1, sizeof(char*));
  char* str_copy = strdup(str);
  char* token = strtok(str_copy, delims);

  for (int i = 0; i < count && token; ++i) {
    tokens[i] = strdup(token);
    token = strtok(NULL, delims);
  }

  free(str_copy);

  return tokens;
}

void free_tokens(char** tokens) {
  if (!tokens) return;
  for (int i = 0; tokens[i]; i++) free(tokens[i]);
  free(tokens);
}

char* join_path(const char* dir, const char* cmd) {
  if (!dir || !cmd) return NULL;

  size_t len = strlen(dir) + strlen(cmd) + 2;
  char* full_path = malloc(len);

  if (full_path) snprintf(full_path, len, "%s/%s", dir, cmd);

  return full_path;
}

char* find_executable_path(const char* cmd, char** dirs) {
  if (!cmd || !dirs) return NULL;

  for (int i = 0; dirs[i] != NULL; i++) {
    char* full_path = join_path(dirs[i], cmd);
    if (access(full_path, X_OK) == 0) return full_path;
    free(full_path);
  }

  return NULL;
}