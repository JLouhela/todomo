/* todo.h - structure of a single todo item */

#ifndef _TODO_H
#define _TODO_H

#define TODO_LEN 255

typedef struct todo
{
    char text[TODO_LEN + 1];
} todo;

todo create_todo(const char *text);

#endif /* _TODO_H */