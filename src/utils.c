
#define _POSIX_C_SOURCE 200809L
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_path(const char* path) {
  if (path == NULL) return NULL;

  int count = 0;
  char* tmp = strdup(path);

  if (strtok(tmp, ":")) {
    count = 1;
    while (strtok(NULL, ":")) count++;
  }

  free(tmp);

  char** dirs = malloc(sizeof(char*) * (count + 1));
  char* path_copy = strdup(path);
  char* token = strtok(path_copy, ":");
  int i = 0;

  while (token) {
    dirs[i++] = strdup(token);
    token = strtok(NULL, ":");
  }

  dirs[i] = NULL;

  free(path_copy);
  return dirs;
}

char* join_path(const char* dir, const char* cmd) {
  if (!dir || !cmd) return NULL;

  size_t len = strlen(dir) + strlen(cmd) + 2;
  char* full_path = malloc(len);

  if (full_path) snprintf(full_path, len, "%s/%s", dir, cmd);

  return full_path;
}

void free_path_array(char** dirs) {
  if (!dirs) return;
  for (int i = 0; dirs[i]; i++) free(dirs[i]);
  free(dirs);
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