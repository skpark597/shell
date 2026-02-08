#include "context.h"

#include "stdlib.h"
#include "utils.h"

t_context g_ctx;

void init_context(void) {
  g_ctx.is_running = 1;
  g_ctx.last_exit_status = 0;

  update_paths();
}

void update_paths(void) {
  if (g_ctx.paths) free_tokens(g_ctx.paths);

  char* env_path = getenv("PATH");
  g_ctx.paths = env_path ? split_tokens(env_path, ":") : NULL;
}

void cleanup_context(void) {
  if (g_ctx.paths) free_tokens(g_ctx.paths);
}