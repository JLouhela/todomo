#include <string.h>
#include <stdlib.h>

#include "todo_writer.h"
#include "todo.h"

int todo_writer_save_todo(const struct Todo *const todo, const char const *todomo_folder_path)
{
    // Create file path from todo id
    char file_path[512];
    if (strlen(todomo_folder_path) + 6 > sizeof(file_path))
    {
        fprintf(stderr, "Failed to save todo: todomo folder path too long\n");
        return TS_FILE_PATH_TOO_LONG;
    }
    // Add leading zeros to todo->id
    sprintf(file_path, "%s/todo_%06d", todomo_folder_path, todo->id);
    FILE *dst = fopen(file_path, "w");
    if (dst == NULL)
    {
        fprintf(stderr, "Failed to save todo: cannot write to '%s'\n", file_path);
        return TS_CANNOT_OPEN_FILE;
    }
    // Write todo to file
    fprintf(dst, "%s,%s,%d", todo->timestamp, todo->text, todo->state);
    fclose(dst);
    return 0;
}