/* cli.h - command line interface definition */

#ifndef _CLI_H
#define _CLI_H

#include "cli_operations.h"

void print_usage();
enum operation get_operation(const char const *arg);
void perform_operation(enum operation op, const char const *todomo_folder, const void *op_args);
void *get_op_args(enum operation op, char *argv[], int arg_start, int argc);

#endif /* _CLI_H */