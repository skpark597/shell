#ifndef UTILS_H
#define UTILS_H

char** split_tokens(const char* path, const char* delim);
void free_tokens(char** dirs);

char* join_path(char* dir, char* cmd);
char* find_executable_path(char** dirs, char* cmd);

#endif