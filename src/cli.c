#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "todo.h"
#include "todosaver.h"

void _perform_add_operation(char const *file_path, const OpAddArgs *add_args);
OpAddArgs *_get_op_add_args(char *argv[], int arg_start, int argc);

void print_usage()
{
    printf("todomo usage: todomo <command> <args>"
           "\n add <todo description>: add new todo"
           "\n init : init new todomo project"
           "\n list <count> : list existing todos, argument optional"
           "\n remove <index> : remove todo by index\n");
}

enum operation get_operation(const char const *arg)
{
    if (!arg)
    {
        return op_invalid;
    }
    if (strcmp(arg, OPERATION_ADD) == 0)
    {
        return op_add;
    }
    if (strcmp(arg, OPERATION_INIT) == 0)
    {
        return op_init;
    }
    if (strcmp(arg, OPERATION_LIST) == 0)
    {
        return op_list;
    }
    if (strcmp(arg, OPERATION_REMOVE) == 0)
    {
        return op_remove;
    }
    return op_invalid;
}

void perform_operation(const enum operation op, const char *file_path, const void *op_args)
{
    switch (op)
    {
    case op_add:
    {
        OpAddArgs *add_args = (OpAddArgs *)op_args;
        _perform_add_operation(file_path, add_args);
        break;
    }
    case op_list:
    {
        break;
    }
    default:
    {
        fprintf(stderr, "unhandled operation %d\n", (int)op);
        break;
    }
    }
}

void _perform_add_operation(const char const *file_path, const OpAddArgs *add_args)
{
    printf("Adding todo: `%s'\n", add_args->description);
    char desc[TODO_LEN];
    strncpy(desc, add_args->description, TODO_LEN);
    const Todo t = create_todo(desc);
    printf("created todo with desc `%s'\n", t.text);
    if (todo_save(&t, file_path) != 0)
    {
        fprintf(stderr, "Failed to save todo '%s' to '%s'\n", desc, file_path);
    }
}

void *get_op_args(enum operation op, char *argv[], int arg_start, int argc)
{
    // TODO: build struct depending on the type, cast to void and return
    switch (op)
    {
    case op_add:
    {
        OpAddArgs *op_add_args = _get_op_add_args(argv, arg_start, argc);
        void *ret = (void *)op_add_args;
        return ret;
    }

    case op_list:
    {
        printf("TODO");
        break;
    }
    case op_init:
    case op_invalid:
    default:
    {
        break;
    }
    }
    return NULL;
}

OpAddArgs *_get_op_add_args(char *argv[], int arg_start, int argc)
{
    OpAddArgs *output = (OpAddArgs *)malloc(sizeof(OpAddArgs));
    if (argc < 3)
    {
        return output;
    }
    strcpy(output->description, argv[2]);

    for (int i = arg_start + 1; i < argc; ++i)
    {
        strcat(output->description, " ");
        strcat(output->description, argv[i]);
    }
    return output;
}