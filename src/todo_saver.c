#include <string.h>
#include <stdlib.h>

#include "todo_saver.h"
#include "todo.h"

bool todo_saver_save_todo(const struct Todo *const todo, const char const *file_path)
{
    char tmp_file_path[PATH_MAX];
    strcpy(tmp_file_path, file_path);
    strcat(tmp_file_path, ".tmp");

    FILE *dst = fopen(file_path, "r");
    if (dst == NULL)
    {
        fprintf(stderr, "Failed to perform add op: cannot write to '%s'\n", file_path);
        return false;
    }

    FILE *tmp_dst = fopen(tmp_file_path, "w");
    if (tmp_dst == NULL)
    {
        fprintf(stderr, "Failed to perform add op: could not create tmp file '%s'\n", tmp_file_path);
        fclose(dst);
        return false;
    }

    fwrite(todo, sizeof(Todo), 1, tmp_dst);
    size_t read_ret = 0;
    size_t write_ret = 0;
    unsigned char buffer[8192];

    // copy to tmp
    do
    {
        read_ret = fread(buffer, 1, sizeof buffer, dst);
        if (read_ret != 0)
        {
            write_ret = fwrite(buffer, 1, read_ret, tmp_dst);
        }
        else
        {
            write_ret = 0;
        }
    } while ((read_ret > 0) && (read_ret == write_ret));
    fclose(dst);
    fclose(tmp_dst);

    int remove_ret = remove(file_path);
    int rename_ret = -1;
    if (remove_ret != 0)
    {
        fprintf(stderr, "Failed to delete original file '%s', cannot rename tmp\n", file_path);
    }
    else
    {
        rename_ret = rename(tmp_file_path, file_path);
        if (rename_ret)
        {
            fprintf(stderr, "Failed to rename tmp file '%s', cannot restore original\n", tmp_file_path);
        }
    }
    return remove_ret == 0 && rename_ret == 0;
}