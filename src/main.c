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
void print_usage();

int main(int argc, char *argv[])
{

    /* 07 variable declarations */
    todo t;
    /* 08 check argv[0] to see how the program was invoked */
    /* 09 process the command line options from the user */
    int opt;
    while ((opt = getopt(argc, argv, ":hap:")) != -1)
        switch (opt)
        {
        case 'h':
            print_usage();
            break;
        case ':':
            switch (optopt)
            {
            case 'p':
                printf("option -%c with default argument value\n", optopt);
                break;
            default:
                fprintf(stderr, "option -%c is missing a required argument\n", optopt);
                return EXIT_FAILURE;
            }
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

void print_usage()
{
    printf("todomo usage: todomo -args"
           "\n-h: help"
           "\n-a: add todo"
           "\n-p <count>: print todos\n");
}
/* 11 ancillary functions if any */