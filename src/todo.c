#include "todo.h"
#include <string.h>

todo create_todo(const char *text)
{
    todo t;
    strncpy(t.text, text, TODO_LEN);
    return t;
}