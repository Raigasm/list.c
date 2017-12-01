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


bool sameString (char *first, char *second){
    return strcmp(first, second) == 0;
}

static char * test_copyString()
{
    char *foo = "foo";
    char *bar = "bar";
    char *foobar = "foobar";
    char *llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch = "llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch";
    char *supercalifragilisticexpialidocious = "supercalifragilisticexpialidocious";

    char output[256]; 
    copyString(foo, output);
    mu_assert("short string (foo) can be copied", sameString(output, "foo"));
    copyString(bar, output);
    mu_assert("short string (bar) can be copied", sameString(output, "bar"));
    copyString(foobar, output);
    mu_assert("longer string should be able to overwrite shorter string", sameString(output, "foobar"));
    copyString(llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch, output);
    mu_assert("ridiculously long strings can be copied", sameString(output, "llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch"));
    copyString(supercalifragilisticexpialidocious, output);
    mu_assert("supercalifragilisticexpialidocious can be copied", sameString(output, "supercalifragilisticexpialidocious"));
    return 0;
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
    
    return 0;
}

static char * test_isLeaf()
{
    printf("running test for isLeaf\n");
    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    fileInfo *data = malloc(sizeof(fileList)); // TODO: release memory
    data->name = filename;
    data->path = path;

    node *leaf = malloc(sizeof(node));
    node *notLeaf = malloc(sizeof(node));
    node *anotherLeaf = malloc(sizeof(node));

    leaf->data = data;
    leaf->leftChild = NULL;
    leaf->rightChild = NULL;
    leaf->parent = notLeaf;

 
    anotherLeaf->data = data;
    anotherLeaf->leftChild = NULL;
    anotherLeaf->rightChild = NULL;
    anotherLeaf->parent = notLeaf;


    notLeaf->data = data;
    notLeaf->leftChild = leaf;
    notLeaf->rightChild = anotherLeaf;
    notLeaf->parent = notLeaf;

    mu_assert("isLeaf should return true if node has no children (leaf)", isLeaf(leaf));
    mu_assert("isLeaf should return true if node has no children (anotherLeaf)", isLeaf(anotherLeaf));
    mu_assert("isLeaf should return false if node has any children", !isLeaf(notLeaf));

    return 0;
}

static char * test_getFilename()
{
    printf("running test for getFilename\n");
    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    fileInfo *data = malloc(sizeof(fileList)); // TODO: release memory
    data->name = filename;
    data->path = path;
    char output[7];
    getFilename(data, output);
    int result = strcmp(output, "foo.bar");
    
    mu_assert("getFilename should return filename", result == 0);
    return 0;
}

static char * test_getPath()
{
    printf("running test for getPath\n");
    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    fileInfo *data = malloc(sizeof(fileList)); // TODO: release memory
    data->name = filename;
    data->path = path;
    DEBUG_PRINT("data.name = %s\n", data->name);
    DEBUG_PRINT("data.path = %s\n", data->path);
    char output[22];
    getPath(data, output);
    printf("output is %s\n", output);
    int result = strcmp(output, "/full/path/to/foo.bar");

    mu_assert("getPath should return path", result == 0);
    return 0;
}

static char * test_getDirectoryContents()
{
    printf("running test for getDirectoryContents\n");
    mu_assert("test_getDirectoryContents not yet implemented", false); 
    return 0;
}

static char * test_printInstructions()
{
    printf("running test for printInstructions\n");
    mu_assert("test_printInstructions not yet implemented", false);
    return 0;
}

static char * test_parseInput()
{
    printf("running test for parseInput\n");
    mu_assert("test_parseInput not yet implemented", false);
    return 0;
}

static char * test_currentDirectory()
{
    printf("running test for currentDirectory\n");
    mu_assert("test_currentDirectory not yet implemented", false);
    return 0;
}

static char * test_customDirectory()
{
    printf("running test for customDirectory\n");
    mu_assert("test_customDirectory not yet implemented", false);
    return 0;
}

static char * test_createNode()
{
    printf("running test for createNode\n");
    mu_assert("test_createNode not yet implemented", false);
    return 0;
}

static char * test_insertNode()
{
    printf("running test for insertNode\n");
    mu_assert("test_insertNode not yet implemented", false);
    return 0;
}

static char * test_printTree()
{
    printf("running test for printTree\n");
    mu_assert("test_printTree not yet implemented", false);
    return 0;
}

static char * test_deleteNode()
{
    printf("running test for deleteNode\n");
    mu_assert("test_deleteNode not yet implemented", false);
    return 0;
}

static char * test_makeTree()
{
    printf("running test for makeTree\n");
    mu_assert("test_makeTree not yet implemented", false);
    return 0;
}

static char * test_destroyTree()
{
    printf("running test for destroyTree\n");
    mu_assert("test_destroyTree not yet implemented", false);
    return 0;
}

static char * test_searchFor()
{
    printf("running test for searchFor\n");
    mu_assert("test_searchFor not yet implemented", false);
    return 0;
}

static char * test_printResults()
{
    printf("running test for printResults\n");
    mu_assert("test_printResults not yet implemented", false);
    return 0;
}

static char * all_tests () {
    mu_run_test(test_copyString);
    mu_run_test(test_isRoot);
    mu_run_test(test_isLeaf);
    mu_run_test(test_getPath);
    mu_run_test(test_getFilename);
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