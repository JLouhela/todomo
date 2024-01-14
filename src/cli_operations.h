/* cli.h - command line interface operations and arg definitions */

#ifndef _CLI_OPERATIONS_H
#define _CLI_OPERATIONS_H

#include <linux/limits.h>
#include "constants.h"

static const char *OPERATION_ADD = "add";
static const char *OPERATION_REMOVE = "remove";
static const char *OPERATION_LIST = "list";
static const char *OPERATION_INIT = "init";
static const char *OPERATION_EXPORT = "export";

enum operation
{
    op_invalid = 0,
    op_add = 1,
    op_remove = 2,
    op_list = 3,
    op_init = 4,
    op_export = 5,
};

enum export_type
{
    export_md = 0
};

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
} OpInitArgs;

typedef struct OpExportArgs
{
    int type;
    char output_file_path[PATH_MAX];
} OpExportArgs;

#endif /* _CLI_OPERATIONS_H */