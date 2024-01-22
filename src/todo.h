/* todo.h - structure of a single todo item */

#ifndef _TODO_H
#define _TODO_H

#include "constants.h"
#include "todo_state.h"
#include <stdint.h>

typedef int32_t todo_id_t;
typedef uint32_t todo_timestamp_t;

enum SerializationOrder
{
    TSO_TIMESTAMP = 0,
    TSO_TEXT = 1,
    TSO_STATE = 2,
    TSO_USER_NAME = 3,
};

typedef struct Todo
{
    todo_id_t id;
    char text[TODO_LEN];
    todo_state_t state;
    unsigned long timestamp;
    char user_name[USER_NAME_LEN];
} Todo;

Todo create_todo(todo_timestamp_t timestamp, const char *text, todo_id_t id, todo_state_t state, const char const *user_name);

#endif /* _TODO_H */