#include <string.h>
#include <stdlib.h>

#include "todo_saver.h"
#include "todo.h"

void todo_save(const struct Todo *const todo, FILE *file)
{
    fwrite(todo, sizeof(Todo), 1, file);
}