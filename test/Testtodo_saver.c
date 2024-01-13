
#define _XOPEN_SOURCE 500 

#include "unity.h"
#include "todo_saver.h"
#include <errno.h>
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include <stdlib.h>

#define TEST_TMP_DIR "Testtodo_writer_tmp"

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

void test_dummy()
{
}


// TEST CASES END


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_dummy);
    UNITY_END();

    return 0;
}
