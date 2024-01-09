/* todo_reader.h - todomo reading functionality */

#ifndef _TODOREADER_H
#define _TODOREADER_H

#include <stdio.h>
#include <stdbool.h>
#include "todo.h"

int todo_reader_read_amount(int amount, const char const *todomo_folder_path, Todo *todos);

todo_id_t todo_reader_get_last_id(const char const *todomo_folder_path);

int todo_reader_count(const char const *todomo_folder_path);

#endif /* _TODOREADER_H */