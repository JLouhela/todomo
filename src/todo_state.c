#include "todo_state.h"
#include <string.h>

void todo_state_to_string(todo_state_t state, char *buffer)
{
    if (buffer == 0)
    {
        return;
    }
    switch (state)
    {
    case TODO_STATE_DONE:
    {
        strcpy(buffer, "TODO_STATE_DONE");
        return;
    }
    case TODO_STATE_CANCEL:
    {
        strcpy(buffer, "TODO_STATE_CANCEL");
        return;
    }
    case TODO_STATE_OPEN:
    {
        strcpy(buffer, "TODO_STATE_OPEN");
        return;
    }
    case TODO_STATE_WIP:
    {
        strcpy(buffer, "TODO_STATE_WIP");
        return;
    }
    }
    return;
}