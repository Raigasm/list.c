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

static char * test_isRoot()
{   
    printf("running test for isRoot\n");
    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    fileInfo *data = malloc(sizeof(fileList)); // TODO: release memory
    data->name = filename;
    data->path = path;

    node *root = malloc(sizeof(node));
    root->data = data;
    root->leftChild = NULL;
    root->rightChild = NULL;
    root->parent = NULL; 

    node *notRoot = malloc(sizeof(node));
    notRoot->data = data;
    notRoot->leftChild = NULL;
    notRoot->rightChild = NULL;
    notRoot->parent = root;

    mu_assert("isRoot should return true if node has no parent", isRoot(root));
    mu_assert("isRoot should return false if node has a parent", !isRoot(notRoot));
}

static char * test_isLeaf()
{
    printf("running test for isLeaf\n");
    return 0;
}

static char * test_getFilename()
{
    printf("running test for getFilename\n");
    return 0;
}

static char * test_getPath()
{
    printf("running test for getPath\n");
    return 0;
}

static char * test_getDirectoryContents()
{
    printf("running test for getDirectoryContents\n");
    return 0;
}

static char * test_printInstructions()
{
    printf("running test for printInstructions\n");
    return 0;
}

static char * test_parseInput()
{
    printf("running test for parseInput\n");
    return 0;
}

static char * test_currentDirectory()
{
    printf("running test for currentDirectory\n");
    return 0;
}

static char * test_customDirectory()
{
    printf("running test for customDirectory\n");
    return 0;
}

static char * test_createNode()
{
    printf("running test for createNode\n");
    return 0;
}

static char * test_insertNode()
{
    printf("running test for insertNode\n");
    return 0;
}

static char * test_printTree()
{
    printf("running test for printTree\n");
    return 0;
}

static char * test_deleteNode()
{
    printf("running test for deleteNode\n");
    return 0;
}

static char * test_makeTree()
{
    printf("running test for makeTree\n");
    return 0;
}

static char * test_destroyTree()
{
    printf("running test for destroyTree\n");
    return 0;
}

static char * test_searchFor()
{
    printf("running test for searchFor\n");
    return 0;
}

static char * test_printResults()
{
    printf("running test for printResults\n");
    return 0;
}

static char * all_tests () {
    mu_run_test(test_getPath);
    mu_run_test(test_getFilename);
    mu_run_test(test_isRoot);
    mu_run_test(test_isLeaf);
    mu_run_test(test_getDirectoryContents);
    mu_run_test(test_printInstructions);
    mu_run_test(test_parseInput);
    mu_run_test(test_currentDirectory);
    mu_run_test(test_customDirectory);
    mu_run_test(test_createNode);
    mu_run_test(test_insertNode);
    mu_run_test(test_printTree);
    mu_run_test(test_deleteNode);
    mu_run_test(test_makeTree);
    mu_run_test(test_destroyTree);
    mu_run_test(test_searchFor);
    mu_run_test(test_printResults);
    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}