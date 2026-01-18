#ifndef UTILS_H
#define UTILS_H

char* join_path(const char* dir, const char* cmd);
char** split_path(const char* path);
void free_path_array(char** dirs);

#endif