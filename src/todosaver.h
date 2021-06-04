/* todosaver.h - todomo saving functionality */

#ifndef _TODOSAVER_H
#define _TODOSAVER_H

#include <stdio.h>

struct Todo;
int todo_save(const struct Todo *const todo, const char const *filePath);

#endif /* _TODOSAVER_H */