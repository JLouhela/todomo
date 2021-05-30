#include "todosaver.h"
#include "todo.h"

int todo_save(const struct todo *const todo, char *filePath)
{
    FILE *dst = fopen(filePath, "wb");
    if (dst != NULL)
    {
        fwrite(todo, sizeof(todo), 1, dst);
        fclose(dst);
        return 0;
    }
    return -1;
}