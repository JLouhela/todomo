#include "git_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *git_utils_get_user_name()
{
    FILE *proc = popen("git config --get user.name", "r");
    char *name = malloc(256);
    if (!name)
    {
        fprintf(stderr, "Cannot allocate memory");
        return NULL;
    }
    if (!proc)
    {
        fprintf(stderr, "Cannot execute git config");
        perror("popen");
        strncpy(name, "Unknown User", 256);
        return NULL;
    }
    // Copy proc output to name
    fgets(name, 256, proc);
    // Remove trailing newline
    name[strlen(name) - 1] = '\0';
    pclose(proc);
    return name;
}
