/* todoreader.h - todomo reading functionality */

#ifndef _TODOREADER_H
#define _TODOREADER_H

#include <stdio.h>
#include "todo.h"

Todo todo_read(int index, FILE *src);

#endif /* _TODOREADER_H */