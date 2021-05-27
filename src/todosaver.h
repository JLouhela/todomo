/* todosaver.h - todomo saving functionality */

#ifndef _TODOSAVER_H
#define _TODOSAVER_H

#include <stdio.h>

struct todo;
int todo_save(const struct todo *const todo, FILE *dst);

#endif /* _TODOSAVER_H */