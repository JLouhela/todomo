#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>

#include "todo.h"
#include "todo_writer.h"
#include "todo_reader.h"
#include "git_utils.h"
#include "todo_state.h"
#include "constants.h"

void _perform_add_operation(char const *file_path, const OpAddArgs *add_args, const char const *user_name);
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

void perform_operation(const enum operation op, const char *todomo_folder, const void *op_args)
{
    switch (op)
    {
    case op_add:
    {
        OpAddArgs *add_args = (OpAddArgs *)op_args;
        char *user_name = git_utils_get_user_name();
        _perform_add_operation(todomo_folder, add_args, user_name);
        free(add_args);
        free(user_name);
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
        _perform_list_operation(todomo_folder, list_args);
        free(list_args);
        break;
    }
    case op_export:
    {
        OpExportArgs *export_args = (OpExportArgs *)op_args;
        _perform_export_operation(todomo_folder, export_args);
        free(export_args);
        break;
    }
    default:
    {
        fprintf(stderr, "unhandled operation %d\n", (int)op);
        break;
    }
    }
}

void _perform_add_operation(const char const *todomo_folder, const OpAddArgs *add_args, const char const *user_name)
{
    char desc[TODO_LEN];
    strncpy(desc, add_args->description, TODO_LEN);

    todo_id_t last_id = todo_reader_get_last_id(todomo_folder);
    if (last_id == TR_CANNOT_OPEN_FOLDER)
    {
        fprintf(stderr, "Failed to perform add op: folder deos not exist");
        return;
    }
    else if (last_id == TR_NO_TODOS_IN_FOLDER)
    {
        last_id = 0;
    }
    todo_timestamp_t timestamp = (todo_timestamp_t)time(NULL);
    const Todo t = create_todo(timestamp, desc, last_id + 1, TODO_STATE_OPEN, user_name);
    todo_writer_save_todo(&t, todomo_folder);
}

void _perform_list_operation(char const *todomo_folder, const OpListArgs *list_args)
{
    int count = DEFAULT_LIST_COUNT;
    if (list_args && list_args->count > 0)
    {
        count = list_args->count;
    }

    const int max_count = todo_reader_count(todomo_folder);
    count = max_count < count ? max_count : count;

    if (count <= 0)
    {
        return;
    }

    Todo todos[count];
    const int todo_read_count = todo_reader_read_amount(count, todomo_folder, todos);
    for (int i = 0; i < todo_read_count; ++i)
    {
        Todo *t = &todos[i];
        char state_str[TODO_STATE_BUFFER_LEN];
        todo_state_to_string(t->state, state_str);
        char timestamp_str[26];
        ctime_r(&t->timestamp, timestamp_str);
        timestamp_str[strlen(timestamp_str) - 1] = '\0';
        printf("TODO [%s] %d: %s. %s, created %s\n", t->user_name, t->id, t->text, state_str, timestamp_str);
    }
}

void _perform_export_operation(char const *todomo_folder, const OpExportArgs *export_args)
{
    printf("TODO: print md to %s\n", export_args->output_file_path);
}

void _perform_init_operation(const OpInitArgs *init_args)
{
    char file_path[PATH_MAX];
    strcpy(file_path, TODOMO_FOLDER);
    if (mkdir(file_path, 0755) && errno != EEXIST)
    {
        printf("error while trying to create todomo root folder (%s)\n", file_path);
        perror("mkdir");
        return;
    }
    printf("Initialized new todomo repository\n");
}

void *get_op_args(enum operation op, char *argv[], int arg_start, int argc)
{
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
    strcpy(output->output_file_path, "TODO.md");
    return output;
}