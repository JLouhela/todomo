#include "todo.h"
#include <string.h>

Todo create_todo(const char *text)
{
    Todo t;
    strncpy(t.text, text, TODO_LEN);
    return t;
}