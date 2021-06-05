#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "cli.h"

bool todomo_dir_exists(const char *const root);
bool find_todomo_repository(char *repo_root_output);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
    enum operation op = get_operation(argv[1]);
    if (op == op_invalid)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    if (op == op_init && todomo_dir_exists("."))
    {
        fprintf(stderr, "todomo repository already present in current directory\n");
        exit(EXIT_FAILURE);
    }
    char todomo_dir[PATH_MAX];
    if (op != op_init && !find_todomo_repository(todomo_dir))
    {
        fprintf(stderr, "not in a todomo repository\n");
        exit(EXIT_FAILURE);
    }

    void *op_args = get_op_args(op, argv, 2, argc);

    char binary_path[PATH_MAX];
    strcpy(binary_path, todomo_dir);
    strcat(binary_path, "/todomo.bin");
    perform_operation(op, binary_path, op_args);

    exit(EXIT_SUCCESS);
}

bool todomo_dir_exists(const char *const root)
{
    char tmp_path[strlen(root) + strlen(TODOMO_FOLDER) + 1];
    strcpy(tmp_path, root);
    strcat(tmp_path, "/");
    strcat(tmp_path, TODOMO_FOLDER);

    DIR *dir = opendir(tmp_path);
    if (dir)
    {
        closedir(dir);
        return true;
    }
    return false;
}

bool find_todomo_repository(char *todomo_folder_output)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        while (cwd != NULL && strlen(cwd) > 0)
        {
            if (todomo_dir_exists(cwd))
            {
                strcpy(todomo_folder_output, cwd);
                strcat(todomo_folder_output, "/");
                strcat(todomo_folder_output, TODOMO_FOLDER);
                return true;
            }
            char *sep = strrchr(cwd, '/');
            if (sep != NULL)
            {
                *sep = 0;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        perror("getcwd() error");
        return false;
    }
    return false;
}