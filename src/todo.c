#include "todo.h"
#include <string.h>

Todo create_todo(const char *text, id_t id, todo_state_t state)
{
    Todo t;
    strncpy(t.text, text, TODO_LEN);
    t.id = id;
    t.state = state;
    return t;
}