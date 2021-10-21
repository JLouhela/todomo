/* todo_saver.h - todomo saving functionality */

#ifndef _TODOSAVER_H
#define _TODOSAVER_H

#include <stdio.h>

struct Todo;
void todo_save(const struct Todo *const todo, FILE *file);

#endif /* _TODOSAVER_H */