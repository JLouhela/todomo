#include <string.h>
#include <stdlib.h>

#include "todosaver.h"
#include "todo.h"

// TODO get FILE* in to align with todoreader.h
int todo_save(const struct Todo *const todo, const char const *file_path)
{
    FILE *dst = fopen(file_path, "a");
    if (dst != NULL)
    {
        printf("writing todo to %s..\n", file_path);
        fwrite(todo, sizeof(Todo), 1, dst);
        fclose(dst);
        return 0;
    }
    return -1;
}