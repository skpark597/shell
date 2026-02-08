#ifndef BUILTINS_H
#define BUILTINS_H

typedef struct {
  char* name;
  void (*func)(char**);
} Builtin;

extern Builtin builtins[];

int find_builtin_idx(char* cmd);
int execute_builtin(char** args);

void do_echo(char** args);
void do_exit(char** args);
void do_type(char** args);
void do_pwd(char** args);
void do_cd(char** args);

#endif