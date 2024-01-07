
#include "unity.h"
#include "cli.h"

void fail_case();

void setUp()
{

}

void tearDown()
{

}

int main(void)
{
    UNITY_BEGIN();

    /*
     * Add in between
     * RUN_TEST(func_name); 
     */

    RUN_TEST(fail_case);

    printf("vittu");
    UNITY_END();

    return 0;
}

void fail_case()
{
    TEST_ASSERT_EQUAL(0,1);
}