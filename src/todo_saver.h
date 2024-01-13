/* todo_saver.h - todomo saving functionality */

#ifndef _TODOSAVER_H
#define _TODOSAVER_H

#include <stdio.h>
#include <stdbool.h>

struct Todo;
bool todo_saver_save_todo(const struct Todo *const todo, const char const *file_path);

#endif /* _TODOSAVER_H */