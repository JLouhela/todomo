
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

int create_file(const char* const file_path, const char* str)
{
    FILE* fp = fopen(file_path, "w");
    if (!fp)
    {
        perror("fopen");
        return -1;
    }
    fprintf(fp, "%s", str);
    fclose(fp);
    return 0;
}

void setup_test_files_with_content(int count, int name_index, const char* text, todo_state_t state)
{
    for (int i = 0; i < count; ++i, ++name_index)
    {
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/test_file_%d", TEST_TMP_DIR, name_index);
        char str[256];
        snprintf(str, sizeof(str), "%s,%d", text, state);
        create_file(file_path, str);
    } 
}

void setup_test_files(int count, int name_index)
{
    setup_test_files_with_content(count, name_index, "TEST TODO :D", TODO_STATE_DONE);
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

void test_last_id()
{
    setup_test_files(5, 100);
    todo_id_t last_id = todo_reader_get_last_id(TEST_TMP_DIR);
    TEST_ASSERT_EQUAL(104, last_id);
    setup_test_files(1, 250);
    last_id = todo_reader_get_last_id(TEST_TMP_DIR);
    TEST_ASSERT_EQUAL(250, last_id);
}

void test_last_id_fail()
{
    todo_id_t last_id = todo_reader_get_last_id(TEST_TMP_DIR);
    TEST_ASSERT_EQUAL(-1, last_id);
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/test_file", TEST_TMP_DIR);
    create_file(file_path, "asd");
    last_id = todo_reader_get_last_id(TEST_TMP_DIR);
    TEST_ASSERT_EQUAL(-1, last_id);
    last_id = todo_reader_get_last_id("asdasdasdasdasd12312easdiu1j4");
    TEST_ASSERT_EQUAL(-1, last_id);
}

void assert_equal_todo(Todo expected, todo_id_t id, todo_state_t state, const char* text)
{
    TEST_ASSERT_EQUAL(id, expected.id);
    TEST_ASSERT_EQUAL(state, expected.state);
    TEST_ASSERT_EQUAL_STRING(text, expected.text);
}

void test_read_todo_1()
{
    Todo output[1];
    setup_test_files_with_content(5, 10, "blah blah", TODO_STATE_DONE);
    int count = todo_reader_read_amount(1, TEST_TMP_DIR, output);    
    TEST_ASSERT_EQUAL(1, count);
    TEST_ASSERT_EQUAL(14, output->id);
    TEST_ASSERT_EQUAL(TODO_STATE_DONE, output->state);
    TEST_ASSERT_EQUAL_STRING("blah blah", output->text);

    Todo output2[5];
    setup_test_files_with_content(2, 100, "bleh bleh", TODO_STATE_WIP);
    count = todo_reader_read_amount(5,  TEST_TMP_DIR, output2);
    TEST_ASSERT_EQUAL(5, count);

    // Sorting follows now alphasort in reverse order
    // For more sophisticated approach, own scandir sorting needs to be implemented
    // See https://stackoverflow.com/questions/37971949/scandir-own-filter-function for reference
    assert_equal_todo(output2[0],14, TODO_STATE_DONE, "blah blah");
    assert_equal_todo(output2[1],13, TODO_STATE_DONE, "blah blah");
    assert_equal_todo(output2[2],12, TODO_STATE_DONE, "blah blah");
    assert_equal_todo(output2[3],11, TODO_STATE_DONE, "blah blah");
    assert_equal_todo(output2[4],101, TODO_STATE_WIP, "bleh bleh");
}


// TEST CASES END


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_read_count);
    RUN_TEST(test_read_count_wrong_dir);
    RUN_TEST(test_last_id);
    RUN_TEST(test_last_id_fail);
    RUN_TEST(test_read_todo_1);

    UNITY_END();

    return 0;
}
