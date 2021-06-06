#include "todoreader.h"

bool todo_read(int index, Todo *t, FILE *src)
{
    int ret = fread(t, sizeof(struct Todo), 1, src);
    if (ret == 0)
    {
        return false;
    }
    return true;
}
