#include "todo_reader.h"

bool _todo_read_from_file(Todo *t, FILE *file);
int _get_todo_count(FILE *file);

bool _todo_read_from_file(Todo *t, FILE *file)
{
    int ret = fread(t, sizeof(struct Todo), 1, file);
    if (ret == 0)
    {
        return false;
    }
    return true;
}

int todo_read_amount(int amount, const char const *file_path, Todo *todos)
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

int _get_todo_count(FILE *file)
{
    size_t cur_pos = ftell(file);

    const int fseek_ok = fseek(file, 0, SEEK_END);
    size_t ret = -1;
    if (fseek_ok == 0)
    {
        ret = ftell(file);
    }
    fseek(file, cur_pos, SEEK_SET);
    return ret;
}

int todo_count(const char const *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open todofile (%s) when reading todo count", file_path);
        return false;
    }
    const int count = _get_todo_count(file);
    fclose(file);
    return count;
}

id_t get_last_id(const char const *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open todofile (%s) for next id query", file_path);
        return -1;
    }
    const int todo_count = _get_todo_count(file);

    int ret = -1;
    // Empty file => 0 is ok
    if (todo_count == 0)
    {
        ret = 0;
    }
    else if (todo_count == -1)
    {
        ret = -1;
    }
    else
    {
        rewind(file);

        Todo t;
        bool ok = _todo_read_from_file(&t, file);
        if (ok)
        {
            ret = t.id;
        }
        else
        {
            return -1;
        }
    }

    fclose(file);
    return ret;
}
