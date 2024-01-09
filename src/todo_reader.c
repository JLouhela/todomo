#include "todo_reader.h"
#include <dirent.h>

bool _todo_read_from_file(Todo *t, FILE *file);

bool _todo_read_from_file(Todo *t, FILE *file)
{
    int ret = fread(t, sizeof(struct Todo), 1, file);
    if (ret == 0)
    {
        return false;
    }
    return true;
}

int todo_reader_read_amount(int amount, const char const *file_path, Todo *todos)
{
    FILE *src = fopen(file_path, "r");
    if (src == NULL)
    {
        fprintf(stderr, "Failed to open todofile (%s) when reading todo", file_path);
        return false;
    }

    int read_count = 0;
    do
    {
        bool ret = _todo_read_from_file((todos + read_count), src);
        if (!ret)
        {
            break;
        }
    } while (++read_count < amount);
    fclose(src);
    return read_count;
}

int todo_reader_count(const char const *todomo_folder)
{
    DIR* dir = NULL;
    dir = opendir(todomo_folder); 
    if (!dir) 
    {
        fprintf(stderr, "Failed to open todomo directory %s\n", todomo_folder);
        return -1;
    }
    struct dirent *entry = NULL;
    int count = 0;
    entry = readdir(dir);
    while (entry != NULL)
    {
        if (entry->d_type == DT_REG)
        { 
            // DT_REG = regular file
            count++;
        }
        entry = readdir(dir);
    }
    
    closedir(dir);
    return count;
}

todo_id_t todo_reader_get_last_id(const char const *todomo_folder)
{
   return -1;
}
