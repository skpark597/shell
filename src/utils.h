#ifndef UTILS_H
#define UTILS_H

char* join_path(const char* dir, const char* cmd);
char** split_path(const char* path);
char* join_args(char** args_array);
char* find_executable_path(const char* cmd, char** dirs);
void free_path_array(char** dirs);

#endif