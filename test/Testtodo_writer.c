
#define _XOPEN_SOURCE 500 

#include "unity.h"
#include "todo_writer.h"
#include "todo.h"
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define TEST_TMP_DIR "Testtodo_writer_tmp"

void setUp()
{
    int mkdir_res = mkdir(TEST_TMP_DIR, 0755);
    if (mkdir_res != 0)
    {
        perror("mkdir");
        TEST_FAIL_MESSAGE("Could not create tmp folder");
        exit(1);
    }
}

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    if (rv != 0)
    {
        perror(fpath);
    }

    return rv;
}

void tearDown()
{
    int nftw_res = nftw(TEST_TMP_DIR, unlink_cb, 64, FTW_DEPTH | FTW_PHYS); 
    if (nftw_res != 0) {
        perror("nftw");
        fprintf(stderr, "error cleaning up test files, please delete manually %s", TEST_TMP_DIR);
    }
}

bool file_exists(const char* file_path)
{
    return access(file_path, F_OK) != -1;
}

bool file_content_matches(const char* file_path, const char* file_content)
{
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return false;
    }
    char buffer[512];
    fgets(buffer, 512, fp);
    fclose(fp);
    return strcmp(buffer, file_content) == 0;
}

// TEST CASES START

void test_write_files()
{
    Todo t;
    t.id = 5;
    t.state = 1;
    strcpy(t.text, "Hello World");
    int res = todo_writer_save_todo(&t, TEST_TMP_DIR);
    TEST_ASSERT_EQUAL_INT(0, res);
    // Create string with TEST_TMP_DIR and a file name
    char file_path[512];
    strcpy(file_path, TEST_TMP_DIR);
    strcat(file_path, "/todo_000005"); 

    TEST_ASSERT_TRUE(file_exists(file_path));
    t.id = 666;
    t.state = 2;
    strcpy(t.text, "Remember to greet the world");
    res = todo_writer_save_todo(&t, TEST_TMP_DIR);
    TEST_ASSERT_EQUAL_INT(0, res);
    // Clear file_path
    memset(file_path, 0, 512);
    strcpy(file_path, TEST_TMP_DIR);
    strcat(file_path, "/todo_000666");
    TEST_ASSERT_TRUE(file_exists(file_path));

}

// TEST CASES END


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_write_files);
    UNITY_END();

    return 0;
}
