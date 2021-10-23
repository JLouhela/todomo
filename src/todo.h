/* todo.h - structure of a single todo item */

#ifndef _TODO_H
#define _TODO_H

#include "constants.h"
#include "todo_state.h"
#include <stdint.h>

#define id_t int32_t

typedef struct Todo
{
    id_t id;
    char text[TODO_LEN];
    todo_state_t state;
} Todo;

Todo create_todo(const char *text, id_t id, todo_state_t state);

#endif /* _TODO_H */