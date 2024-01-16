#include "todo_reader.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

bool _read_todo_content_from_file(Todo *t, const char const *file_name);
todo_id_t _parse_id_from_filename(const char const* file_name);
void _parse_todo_from_content(Todo* t, const char const* todo_content);

void _parse_todo_from_content(Todo* t, const char const* todo_content)
{
    // Split todo_content with strtok by ','
    char* token = strtok((char*)todo_content, ",");
    int i = 0;
    while (token != NULL)
    {
        switch (i)
        {
            case TSO_TIMESTAMP:
                t->timestamp = strtoul(token, NULL, 10);
                break;
            case TSO_TEXT:
                strncpy(t->text, token, TODO_LEN);
                break;
            case TSO_STATE:
                t->state = atoi(token);
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        i++;
    } 
}


bool _read_todo_content_from_file(Todo *t, const char const *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open todo file %s\n", file_name);
        perror("fopen");
        return false;
    }

    char buffer[TODO_LEN];
    while (fgets(buffer, TODO_LEN, fp));

    _parse_todo_from_content(t, buffer);

    return true;
}

int todo_reader_read_amount(int amount, const char const *todomo_folder, Todo *todos)
{
    struct dirent **namelist;
    int n = scandir(todomo_folder, &namelist, NULL, alphasort);
    int read_amount = 0;
    if (n < 0) 
    {
        perror("scandir");
        return -1;
    }
    while (n--)
    {
        if (read_amount < amount)
        {
            if (namelist[n]->d_name[0] != '.')
            {
               todo_id_t id = _parse_id_from_filename(namelist[n]->d_name);
                Todo* todo = &todos[read_amount];
                todo->id = id;
                // Get full filepath from namelist[n]
                char file_path[512];
                if (strlen(todomo_folder) + strlen(namelist[n]->d_name) + 1 > sizeof(file_path))
                {
                    fprintf(stderr, "File path too long: %s \n", file_path);
                    continue;
                }
                snprintf(file_path, sizeof(file_path), "%s/%s", todomo_folder, namelist[n]->d_name);
                if (_read_todo_content_from_file(todo, file_path)) {
                    read_amount++;
                }
            }
        }
        free(namelist[n]);
    }
    free(namelist);
    return read_amount;
}

int todo_reader_count(const char const *todomo_folder)
{
    DIR* dir = NULL;
    dir = opendir(todomo_folder); 
    if (!dir) 
    {
        fprintf(stderr, "Failed to open todomo directory %s\n", todomo_folder);
        return -1;
    }
    struct dirent *entry = NULL;
    int count = 0;
    entry = readdir(dir);
    while (entry != NULL)
    {
        if (entry->d_type == DT_REG)
        { 
            // DT_REG = regular file
            count++;
        }
        entry = readdir(dir);
    }
    
    closedir(dir);
    return count;
}

todo_id_t _parse_id_from_filename(const char const* file_name)
{
    todo_id_t id = 0;
    int multiplier = 1;
    for (int i = strlen(file_name) - 1; i >= 0; --i)
    {
        if (isdigit(file_name[i]))
        {
            id += (file_name[i] - '0') * multiplier;
            multiplier *= 10;
        }
        else
        {
            break;
        }
    }
    if (id == 0) 
    {
        // Error
        return -1;
    }
    return id;
}

todo_id_t todo_reader_get_last_id(const char const *todomo_folder)
{
    struct dirent **namelist;
    int n = scandir(todomo_folder, &namelist, NULL, alphasort);
    todo_id_t id = -1;
    if (n < 0) 
    {
        perror("scandir");
        return TR_CANNOT_OPEN_FOLDER;
    }
    while (n--)
    {
        if (id == -1 && namelist[n]->d_name[0] != '.')
        {
            id = _parse_id_from_filename(namelist[n]->d_name);
        }
        free(namelist[n]);
    }
    free(namelist);
    if (id == -1)
    {
        return TR_NO_TODOS_IN_FOLDER;
    }
    return id;
}
