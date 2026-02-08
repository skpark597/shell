#ifndef UTILS_H
#define UTILS_H

int count_tokens(const char* str, const char* delim);
char* join_path(const char* dir, const char* cmd);
char** split_tokens(const char* path, const char* delim);
char* join_args(char** args_array);
char* find_executable_path(const char* cmd, char** dirs);
void free_tokens(char** dirs);

#endif