#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include "todosaver.h"
#include "todo.h"

void recursive_mkdir(const char const *path)
{
    char *sep = strrchr(path, '/');
    if (sep != NULL)
    {
        *sep = 0;
        recursive_mkdir(path);
        *sep = '/';
    }
    if (mkdir(path, 0777) && errno != EEXIST)
    {
        printf("error while trying to create '%s'\n%m\n", path);
    }
}
FILE *fopen_mkdir(const char const *path, const char const *mode)
{
    const char *sep = strrchr(path, '/');
    if (sep)
    {
        char *tmp_path = strdup(path);
        tmp_path[sep - path] = 0;
        recursive_mkdir(tmp_path);
        free(tmp_path);
    }
#include <dirent.h>
    return fopen(path, mode);
}

int todo_save(const struct Todo *const todo, const char const *file_path)
{
    FILE *dst = fopen_mkdir(file_path, "wb");
    if (dst != NULL)
    {
        printf("writing todo to %s..", file_path);
        fwrite(todo, sizeof(todo), 1, dst);
        fclose(dst);
        return 0;
    }
    return -1;
}