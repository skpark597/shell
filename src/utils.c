
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