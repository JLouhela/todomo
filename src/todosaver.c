#include <string.h>
#include <stdlib.h>

#include "todosaver.h"
#include "todo.h"

int todo_save(const struct Todo *const todo, const char const *file_path)
{
    FILE *dst = fopen(file_path, "wb");
    if (dst != NULL)
    {
        printf("writing todo to %s..", file_path);
        fwrite(todo, sizeof(todo), 1, dst);
        fclose(dst);
        return 0;
    }
    return -1;
}