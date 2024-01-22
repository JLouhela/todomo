#include "todo.h"
#include <string.h>

Todo create_todo(todo_timestamp_t timestamp, const char *text, todo_id_t id, todo_state_t state, const char *const user_name)
{
    Todo t;
    t.timestamp = timestamp;
    strncpy(t.text, text, TODO_LEN);
    strncpy(t.user_name, user_name, USER_NAME_LEN);
    t.id = id;
    t.state = state;
    return t;
}