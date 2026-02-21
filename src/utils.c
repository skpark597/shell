#define _POSIX_C_SOURCE 200809L
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* next_token(const char** src, const char* delims) {
  const char* start = *src;

  while (strchr(delims, *start)) start++;
  if (*start == '\0') return NULL;

  char* buffer = malloc(strlen(start) + 1);
  int idx = 0, in_quotes = 0;

  while (*start) {
    if (*start == '\'') {
      in_quotes = !in_quotes;
    } else if (!in_quotes && strchr(delims, *start)) {
      break;
    } else {
      buffer[idx++] = *start;
    }

    start++;
  }
  buffer[idx] = '\0';
  *src = start;

  char* optimized = realloc(buffer, idx + 1);
  return optimized != NULL ? optimized : buffer;
}

char** split_tokens(const char* str, const char* delims) {
  if (str == NULL) return NULL;

  int max_slot = strlen(str) / 2 + 2;
  int idx = 0;
  char** buffer = malloc(sizeof(char*) * max_slot);
  const char* cur = str;

  while (*cur) {
    char* token = next_token(&cur, delims);
    if (token == NULL) break;

    buffer[idx++] = token;
  }

  buffer[idx] = NULL;

  char** optimized = realloc(buffer, sizeof(char*) * (idx + 1));
  return optimized;
}

void free_tokens(char** tokens) {
  if (!tokens) return;
  for (int i = 0; tokens[i]; ++i) free(tokens[i]);
  free(tokens);
}

char* join_path(char* dir, char* cmd) {
  if (!dir || !cmd) return NULL;

  size_t len = strlen(dir) + strlen(cmd) + 2;
  char* full_path = malloc(len);

  if (full_path) snprintf(full_path, len, "%s/%s", dir, cmd);

  return full_path;
}

char* find_executable_path(char** dirs, char* cmd) {
  if (!dirs || !cmd) return NULL;

  for (int i = 0; dirs[i] != NULL; ++i) {
    char* full_path = join_path(dirs[i], cmd);
    if (access(full_path, X_OK) == 0) return full_path;

    free(full_path);
  }

  return NULL;
}