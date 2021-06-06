/* todoreader.h - todomo reading functionality */

#ifndef _TODOREADER_H
#define _TODOREADER_H

#include <stdio.h>
#include <stdbool.h>
#include "todo.h"

bool todo_read(int index, Todo *t, FILE *src);

#endif /* _TODOREADER_H */