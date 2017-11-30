#include "debugprint.h"
#include "minunit.h"
#include "findfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run     = 0;
int tests_failed  = 0;
int suites_run    = 0;
int suites_failed = 0;


static char *test_check_testing_works()
{
    mu_assert("Testing does not work", 7 == 7);
    return 0;
}

void test_setup (void) {
    printf("test_setup\n");
}

void test_teardown (void) {
    printf("test_teardown\n");
}

MU_TEST(test_check)
{
    mu_check(5 == 7);
}

MU_TEST(test_currentDirectory)
{
    printf("test_currentDirectory\n");
}   

MU_TEST(test_customDirectory)
{
    printf("test_customDirectory\n");
}

MU_TEST(test_insert)
{
    printf("test_insert\n");
}

MU_TEST(test_delete) {
    printf("test_delete\n");
}   

MU_TEST(search)
{
    printf("search\n");
}

MU_TEST(results )
{
    printf("results \n");
}

MU_TEST(instructions)
{
    printf("instructions\n");
}

MU_TEST(parseInput)
{
    printf("parseInput\n");
}

MU_TEST(printTree)
{
    printf("printTree\n");
}

MU_TEST(getDirectoryContents)
{
    printf("getDirectoryContents\n");
}

MU_TEST(destroyTree)
{
    printf("destroyTree\n");
}



MU_TEST(test_makeTree)
{
    printf("test_makeTree\n");
}

MU_TEST_SUITE(test_findfile)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_check);
    MU_RUN_TEST(test_currentDirectory);
    MU_RUN_TEST(test_customDirectory);
    MU_RUN_TEST(test_insert);
    MU_RUN_TEST(test_delete);
    MU_RUN_TEST(search);
    MU_RUN_TEST(results);
    MU_RUN_TEST(instructions);
    MU_RUN_TEST(parseInput);
    MU_RUN_TEST(printTree);
    MU_RUN_TEST(getDirectoryContents);
    MU_RUN_TEST(destroyTree);
    MU_RUN_TEST(test_makeTree);
}


int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_findfile);
    MU_REPORT();
    return 0;
}