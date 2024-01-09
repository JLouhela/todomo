
#define _XOPEN_SOURCE 500 

#include "unity.h"
#include "todo_reader.h"
#include <errno.h>
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include <stdlib.h>

#define TEST_TMP_DIR "Testtodo_reader_tmp"

void setUp()
{
    int mkdir_res = mkdir(TEST_TMP_DIR, 0777);
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

int create_file(const char* const file_path)
{
    FILE* file_ptr = fopen(file_path, "w");
    if (!file_ptr)
    {
        perror("fopen");
        return -1;
    }
    fclose(file_ptr);
    return 0;
}

void setup_test_files(int count, int name_index)
{
    for (int i = 0; i < count; ++i, ++name_index)
    {
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/test_file%d", TEST_TMP_DIR, name_index);
        create_file(file_path);
    } 
}

// TEST CASES 
void test_read_count()
{
    setup_test_files(5, 0);    
    int count = todo_reader_count(TEST_TMP_DIR);
    TEST_ASSERT_EQUAL(5, count);
    setup_test_files(5, 5);    
    count = todo_reader_count(TEST_TMP_DIR);
    TEST_ASSERT_EQUAL(10, count);
}

void test_read_count_wrong_dir()
{
    int count = todo_reader_count("asdasdasdasdasdaser33108u3");
    TEST_ASSERT_EQUAL(-1, count);
}
// TEST CASES END


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_read_count);
    RUN_TEST(test_read_count_wrong_dir);

    UNITY_END();

    return 0;
}
