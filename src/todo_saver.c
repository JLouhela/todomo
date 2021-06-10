#include <string.h>
#include <stdlib.h>

#include "todo_saver.h"
#include "todo.h"

// TODO get FILE* in to align with todo_reader.h
int todo_save(const struct Todo *const todo, const char const *file_path)
{
    FILE *dst = fopen(file_path, "a");
    if (dst != NULL)
    {
        fwrite(todo, sizeof(Todo), 1, dst);
        fclose(dst);
        return 0;
    }
    return -1;
}