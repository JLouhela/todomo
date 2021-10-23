/* todo_reader.h - todomo reading functionality */

#ifndef _TODOREADER_H
#define _TODOREADER_H

#include <stdio.h>
#include <stdbool.h>
#include "todo.h"

int todo_read_amount(int amount, const char const *file_path, Todo *todos);

id_t get_last_id(const char const *file_path);

int todo_count(const char const *file_path);

#endif /* _TODOREADER_H */