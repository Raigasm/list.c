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

void test_setup (void) {
    // printf("test_setup\n");
}

void test_teardown (void) {
    // printf("test_teardown\n");
}

MU_TEST(test_isRoot)
{

    printf("running test for isRoot\n");
}

MU_TEST(test_isLeaf)
{
    printf("running test for isLeaf\n");
}

MU_TEST(test_getFilename)
{
    printf("running test for getFilename\n");
}

MU_TEST(test_getPath)
{
    printf("running test for getPath\n");
}

MU_TEST(test_getDirectoryContents)
{
    printf("running test for getDirectoryContents\n");
}

MU_TEST(test_printInstructions)
{
    printf("running test for printInstructions\n");
}

MU_TEST(test_parseInput)
{
    printf("running test for parseInput\n");
}

MU_TEST(test_currentDirectory)
{
    printf("running test for currentDirectory\n");
}

MU_TEST(test_customDirectory)
{
    printf("running test for customDirectory\n");
}

MU_TEST(test_createNode)
{
    printf("running test for createNode\n");
}

MU_TEST(test_insertNode)
{
    printf("running test for insertNode\n");
}

MU_TEST(test_printTree)
{
    printf("running test for printTree\n");
}

MU_TEST(test_deleteNode)
{
    printf("running test for deleteNode\n");
}

MU_TEST(test_makeTree)
{
    printf("running test for makeTree\n");
}

MU_TEST(test_destroyTree)
{
    printf("running test for destroyTree\n");
}

MU_TEST(test_searchFor)
{
    printf("running test for searchFor\n");
}

MU_TEST(test_printResults)
{
    printf("running test for printResults\n");
}


MU_TEST_SUITE(test_findfile)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_isRoot);
    MU_RUN_TEST(test_isLeaf);
    MU_RUN_TEST(test_getDirectoryContents);
    MU_RUN_TEST(test_printInstructions);
    MU_RUN_TEST(test_parseInput);
    MU_RUN_TEST(test_currentDirectory);
    MU_RUN_TEST(test_customDirectory);
    MU_RUN_TEST(test_createNode);
    MU_RUN_TEST(test_insertNode);
    MU_RUN_TEST(test_printTree);
    MU_RUN_TEST(test_deleteNode);
    MU_RUN_TEST(test_makeTree);
    MU_RUN_TEST(test_destroyTree);
    MU_RUN_TEST(test_searchFor);
    MU_RUN_TEST(test_printResults);
}


int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_findfile);
    MU_REPORT();
    return 0;
}