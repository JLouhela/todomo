#include "todo.h"
#include <string.h>

Todo create_todo(todo_timestamp_t timestamp, const char *text, todo_id_t id, todo_state_t state)
{
    Todo t;
    t.timestamp = timestamp;
    strncpy(t.text, text, TODO_LEN);
    t.id = id;
    t.state = state;
    return t;
}