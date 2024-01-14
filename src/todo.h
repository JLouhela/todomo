/* todo.h - structure of a single todo item */

#ifndef _TODO_H
#define _TODO_H

#include "constants.h"
#include "todo_state.h"
#include <stdint.h>

typedef int32_t todo_id_t;

typedef struct Todo
{
    todo_id_t id;
    char text[TODO_LEN];
    todo_state_t state;
    char timestamp[64];
} Todo;

Todo create_todo(const char *text, todo_id_t id, todo_state_t state);

#endif /* _TODO_H */