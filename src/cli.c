#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include "todo.h"
#include "todo_saver.h"
#include "todo_reader.h"
#include "todo_state.h"
#include "constants.h"

void _perform_add_operation(char const *file_path, const OpAddArgs *add_args);
void _perform_list_operation(char const *file_path, const OpListArgs *list_args);
void _perform_init_operation(const OpInitArgs *init_args);
void _perform_export_operation(char const *file_path, const OpExportArgs *export_args);

OpAddArgs *_get_op_add_args(char *argv[], int arg_start, int argc);
OpListArgs *_get_op_list_args(char *argv[], int arg_start, int argc);
OpExportArgs *_get_op_export_args(char *argv[], int arg_start, int argc);
void print_usage();

void print_usage()
{
    printf("todomo usage: todomo <command> <args>"
           "\n add <todo description>: add new todo"
           "\n init : init new todomo project"
           "\n list <count> : list existing todos, argument optional"
           "\n remove <id> : remove todo by id\n");
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
    if (strcmp(arg, OPERATION_EXPORT) == 0)
    {
        return op_export;
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
        free(add_args);
        break;
    }
    case op_init:
    {
        _perform_init_operation(NULL);
        break;
    }
    case op_list:
    {
        OpListArgs *list_args = (OpListArgs *)op_args;
        _perform_list_operation(file_path, list_args);
        free(list_args);
        break;
    }
    case op_export:
    {
        OpExportArgs *export_args = (OpExportArgs *)op_args;
        _perform_export_operation(file_path, export_args);
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
    char desc[TODO_LEN];
    strncpy(desc, add_args->description, TODO_LEN);

    const id_t last_id = get_last_id(file_path);
    if (last_id < 0)
    {
        fprintf(stderr, "Failed to perform add op: could not read last id");
        return;
    }

    const Todo t = create_todo(desc, last_id + 1, TODO_STATE_OPEN);
    todo_save(&t, file_path);
}

void _perform_list_operation(char const *file_path, const OpListArgs *list_args)
{
    int count = DEFAULT_LIST_COUNT;
    if (list_args && list_args->count > 0)
    {
        count = list_args->count;
    }

    const int max_count = todo_count(file_path);
    count = max_count < count ? max_count : count;

    if (count <= 0)
    {
        return;
    }

    Todo todos[count];
    const int todo_read_count = todo_read_amount(count, file_path, todos);
    for (int i = 0; i < todo_read_count; ++i)
    {
        Todo *t = &todos[i];
        char state_str[TODO_STATE_BUFFER_LEN];
        todo_state_to_string(t->state, state_str);
        printf("TODO: %d-%s-%s\n", t->id, state_str, t->text);
    }
}

void _perform_export_operation(char const *file_path, const OpExportArgs *export_args)
{
    printf("TODO: print md to %s\n", export_args->output_file_path);
}

void _perform_init_operation(const OpInitArgs *init_args)
{
    char file_path[PATH_MAX];
    strcpy(file_path, TODOMO_FOLDER);
    if (mkdir(file_path, 0777) && errno != EEXIST)
    {
        printf("error while trying to create todomo root folder (%s)\n", file_path);
        return;
    }
    strcat(file_path, "/");
    strcat(file_path, TODOMO_FILE);
    FILE *file_ptr = fopen(file_path, "w");
    if (file_ptr)
    {
        fclose(file_ptr);
        printf("Initialized new todomo repository\n");
    }
    else
    {
        fprintf(stderr, "Failed to initialize todomo repository, could not create binary\n");
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
        return (void *)op_add_args;
    }

    case op_list:
    {
        OpListArgs *op_list_args = _get_op_list_args(argv, arg_start, argc);
        return (void *)op_list_args;
    }
    case op_export:
    {
        OpExportArgs *op_export_args = _get_op_export_args(argv, arg_start, argc);
        return (void *)op_export_args;
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

// TODO why ptr?
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

OpListArgs *_get_op_list_args(char *argv[], int arg_start, int argc)
{
    OpListArgs *output = (OpListArgs *)malloc(sizeof(OpListArgs));
    output->count = DEFAULT_LIST_COUNT;
    if (argc < 3)
    {
        return output;
    }
    output->count = atoi(argv[arg_start]);
    return output;
}

OpExportArgs *_get_op_export_args(char *argv[], int arg_start, int argc)
{
    OpExportArgs *output = (OpExportArgs *)malloc(sizeof(OpExportArgs));
    // No args supported yet, default to md
    output->type = export_md;
    strcpy(output->output_file_path, "todo.md");
    return output;
}