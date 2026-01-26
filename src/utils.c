
#define _POSIX_C_SOURCE 200809L
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count_tokens(const char* str, char delim) {
  if (str == NULL || *str == '\0') return 0;

  int count = 0;
  int in_segment = 0;

  while (*str) {
    if (*str != delim && in_segment == 0) {
      in_segment = 1;
      count++;
    } else if (*str == delim) {
      in_segment = 0;
    }

    str++;
  }

  return count;
}

char** split_tokens(const char* str, char delim) {
  if (str == NULL) return NULL;

  int count = count_tokens(str, delim);

  char** dirs = malloc(sizeof(char*) * (count + 1));
  if (!dirs) return NULL;

  char* str_copy = strdup(str);
  char delim_str[2] = {delim, '\0'};
  char* token = strtok(str_copy, delim_str);

  int i = 0;

  while (token && i < count) {
    dirs[i++] = strdup(token);
    token = strtok(NULL, delim_str);
  }

  dirs[i] = NULL;
  free(str_copy);

  return dirs;
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

char* join_args(char** args_array) {
  if (args_array[1] == NULL) return NULL;

  int total_len = 0;
  for (int i = 1; args_array[i] != NULL; i++) {
    total_len += strlen(args_array[i]) + 1;
  }

  char* result = (char*)malloc(total_len);
  if (!result) return NULL;

  result[0] = '\0';

  for (int i = 1; args_array[i] != NULL; i++) {
    strcat(result, args_array[i]);
    if (args_array[i + 1] != NULL) {
      strcat(result, " ");
    }
  }

  return result;
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