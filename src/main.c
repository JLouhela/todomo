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
enum op
{
    op_add,
    op_list
};
/* 05 globals (but don't)*/
/* 06 ancillary function prototypes if any */
void print_usage();

int main(int argc, char *argv[])
{

    /* 07 variable declarations */
    todo t;
    /* 08 check argv[0] to see how the program was invoked */
    /* 09 process the command line options from the user */
    int c = -1;
    while (1)
    {
        static struct option long_options[] =
            {
                {"add", required_argument, 0, 'a'},
                {"list", optional_argument, 0, 'l'},
                {"help", no_argument, 0, 'h'},
                {0, 0, 0, 0}};

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, ":a:hl::",
                        long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 'h':
            print_usage();
            break;

        case 'a':
            printf("option -a with value `%s'\n", optarg);
            break;

        case 'l':
            if (optarg)
                printf("option -l with value `%s'\n", optarg);
            else
                printf("option -l with no arg\n");
            break;
        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            abort();
        }
    }

    /* 10 do the needful */
    //todo_save(&t, NULL);
    return 0;
}

void print_usage()
{
    printf("todomo usage: todomo -args"
           "\n-h: help"
           "\n-a <title>;<description>: add todo"
           "\n-l <count>: list todos\n");
}
/* 11 ancillary functions if any */