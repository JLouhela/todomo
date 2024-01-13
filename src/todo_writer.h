/* todo_saver.h - todomo saving functionality */

#ifndef _TODOWRITER_H
#define _TODOWRITER_H

#include <stdio.h>
#include <stdbool.h>

#define TODO_WRITER_MAX_FILE_PATH_LEN 500

enum Save_result
{
    TS_SAVE_SUCCESS = 0,
    TS_FILE_PATH_TOO_LONG = -1,
    TS_CANNOT_OPEN_FILE = -2,
};

struct Todo;
int todo_writer_save_todo(const struct Todo *const todo, const char const *todomo_folder_path);

#endif /* _TODOWRITER_H */