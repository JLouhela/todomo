#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

#include "todo.h"
#include "todosaver.h"

enum op
{
    op_add,
    op_list
};
void print_usage();

int main(int argc, char *argv[])
{
    char file_path[512] = "todomo.bin";
    enum op operation = op_list;
    int c = -1;
    while (1)
    {
        static struct option long_options[] =
            {
                {"add", required_argument, 0, 'a'},
                {"file", required_argument, 0, 'f'},
                {"list", optional_argument, 0, 'l'},
                {"help", no_argument, 0, 'h'},
                {0, 0, 0, 0}};

        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long(argc, argv, ":a:f:hl::",
                        long_options, &option_index);

        // Detect the end of the options.
        if (c == -1)
        {
            break;
        }

        switch (c)
        {
        case 0:
            // If this option set a flag, do nothing else now.
            if (long_options[option_index].flag != 0)
            {
                break;
            }
            printf("option %s", long_options[option_index].name);
            if (optarg)
            {
                printf(" with arg %s", optarg);
            }
            printf("\n");
            break;

        case 'h':
            print_usage();
            break;

        case 'a':
            // TODO handle later, store op
            printf("option -a with value `%s'\n", optarg);
            char desc[TODO_LEN];
            strncpy(desc, optarg, TODO_LEN);
            const todo t = create_todo(desc);
            printf("created todo with desc `%s'\n", t.text);
            break;

        case 'f':
            // TODO logger + log levels
            printf("Set filepath to %s\n", optarg);
            strcpy(file_path, optarg);
            break;

        case 'l':
            if (optarg)
            {
                printf("option -l with value `%s'\n", optarg);
            }
            else
            {
                printf("option -l with no arg\n");
            }
            break;
        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    //todo_save(&t, NULL);
    exit(EXIT_SUCCESS);
}

void print_usage()
{
    printf("todomo usage: todomo -args"
           "\n-h: help"
           "\n-a <todo text>: add todo, max 255 characters"
           "\n-f <file path>: file path (input/output) depending on the context"
           "\n-l <count>: list todos\n");
}
