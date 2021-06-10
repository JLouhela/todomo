/* constants.h - constants across various modules */

#include <limits.h>

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define TODO_LEN 1024
#define DEFAULT_LIST_COUNT INT_MAX

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

static const char *TODOMO_FOLDER = ".todomo";
static const char *TODOMO_FILE = "todomo.bin";

#endif /* _CONSTANTS_H */