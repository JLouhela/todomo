/* todo_reader.h - todomo reading functionality */

#ifndef _TODOREADER_H
#define _TODOREADER_H

#include <stdio.h>
#include <stdbool.h>
#include "todo.h"

enum Read_result
{
    TR_READ_SUCCESS = 0,
    TR_CANNOT_OPEN_FOLDER = -1,
    TR_NO_TODOS_IN_FOLDER = -2,
};

int todo_reader_read_amount(int amount, const char const *todomo_folder, Todo *todos);

todo_id_t todo_reader_get_last_id(const char const *todomo_folder);

int todo_reader_count(const char const *todomo_folder);

#endif /* _TODOREADER_H */