#ifndef CONTEXT_H
#define CONTEXT_H

typedef struct s_context {
  char** paths;
  int last_exit_status;
  int is_running;
} t_context;

extern t_context g_ctx;

void init_context(void);
void update_paths(void);
void cleanup_context(void);

#endif