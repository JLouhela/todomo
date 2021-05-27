/* 00 system includes */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
/* 01 project includes */
#include "todo.h"
#include "todosaver.h"
/* 02 externs */
/* 03 defines */
/* 04 typedefs */
/* 05 globals (but don't)*/
/* 06 ancillary function prototypes if any */

int main(int argc, char *argv[])
{

    /* 07 variable declarations */
    todo t;
    /* 08 check argv[0] to see how the program was invoked */
    /* 09 process the command line options from the user */
    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1)
        switch (opt)
        {
        case 'h':
            printf("\nHELP\n");
            break;
        case '?':
            if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            return 1;
        default:
            abort();
        }

    /* 10 do the needful */
    //todo_save(&t, NULL);
    return 0;
}

/* 11 ancillary functions if any */