#ifndef BUILTINS_H
#define BUILTINS_H

typedef struct {
  char* name;
  void (*func)(char*);
} Builtin;

extern Builtin builtins[];

void do_echo(char* args);
void do_exit(char* args);
void do_type(char* args);

#endif