/* todo.h - structure of a single todo item */

#ifndef _TODO_H
#define _TODO_H

#include "constants.h"

typedef struct Todo
{
    char text[TODO_LEN];
} Todo;

Todo create_todo(const char *text);

#endif /* _TODO_H */