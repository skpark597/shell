#ifndef UTILS_H
#define UTILS_H

int count_tokens(const char* str, const char* delim);
char** split_tokens(const char* path, const char* delim);
void free_tokens(char** dirs);

char* join_path(const char* dir, const char* cmd);
char* find_executable_path(const char* cmd, char** dirs);

#endif