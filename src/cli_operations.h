/* cli.h - command line interface operations and arg definitions */

#ifndef _CLI_OPERATIONS_H
#define _CLI_OPERATIONS_H

#include <linux/limits.h>
#include "constants.h"

static const char *OPERATION_ADD = "add";
static const char *OPERATION_REMOVE = "remove";
static const char *OPERATION_LIST = "list";
static const char *OPERATION_INIT = "init";

enum operation
{
    op_invalid = 0,
    op_add = 1,
    op_remove = 2,
    op_list = 3,
    op_init = 4
};

// TODO define payloads for operations = structs
// deliver as void* to handle_op
typedef struct OpAddArgs
{
    char description[TODO_LEN];
} OpAddArgs;

typedef struct OpListArgs
{
    int count;
} OpListArgs;

typedef struct OpRemoveArgs
{
    int handle;
} OpRemoveArgs;

typedef struct OpInitArgs
{
    char pwd[PATH_MAX];
} OpInitArgs;

#endif /* _CLI_OPERATIONS_H */