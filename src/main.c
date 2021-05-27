/* 00 system includes */
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
    /* 10 do the needful */
    todo_save(&t, NULL);
    return 0;
}

/* 11 ancillary functions if any */