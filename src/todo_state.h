/* todo_state.h - state of a single todo item */

#ifndef _TODO_STATE_H
#define _TODO_STATE_H

#define TODO_STATE_DONE 0
#define TODO_STATE_WIP 1
#define TODO_STATE_OPEN 2
#define TODO_STATE_CANCEL 3

#define todo_state_t int

#define TODO_STATE_BUFFER_LEN 32

void todo_state_to_string(todo_state_t state, char *buffer);

#endif /* _TODO_STATE_H */