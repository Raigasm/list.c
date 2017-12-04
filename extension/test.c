#include "debugprint.h"
#include "minunit.h"
#include "findfile.h"
#include "filelist.h"
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

model *beforeEach (char *testName) {
    DEBUG_PRINT("\n");
    char *testPath = "test_files";
    char *testQuery = "test";
    DEBUG_PRINT("Test %s: configuring model\n", testName);
    return configure(testQuery, testPath);
}

static char * test_copyString()
{
    model *MODEL = beforeEach("copyString");
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
    model *MODEL = beforeEach("isRoot");
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
    model *MODEL = beforeEach("isLeaf");
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

static char *test_configure()
{
    model *MODEL = beforeEach("Configure");
    mu_assert("COUNT should be set properly", MODEL->COUNT == 0);
    mu_assert("DIRECTORY should be set properly", strcmp("test_files", MODEL->DIRECTORY) == 0);
    mu_assert("ALGORITHM should be set properly", MODEL->ALGORITHM == 0);
    mu_assert("LIST should be set properly", MODEL->LIST != NULL);
    mu_assert("TREE  should be set properly", MODEL->TREE != NULL);
    mu_assert("COUNT  should be set properly", MODEL->COUNT == 0);
    
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

static char * test_item_create() {
    model *MODEL = beforeEach("item_create");

    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    char *filenameTwo = "rai.exe";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *filenameThree = "feelings";
    char *pathThree = "/trash/feelings";

    fileListItem *first = item_create(filename);
    fileListItem *second = item_create(filenameTwo);
    fileListItem *third = item_create(filenameThree);

    mu_assert("file list item should be created successfully", first != NULL);
    mu_assert("first file list item should have id of 0", first->id == 0);
    mu_assert("first file list item should have correct name", first->data->name = "foo.bar");
    mu_assert("first file list item should have correct path", first->data->path == "/full/path/to/foo.bar");
    mu_assert("second file list item should be created successfully", second != NULL);
    mu_assert("second file list item should have id of 1", second->id == 1);
    mu_assert("second file list item should have correct name", second->data->name = "rai.exe");
    mu_assert("second file list item should have correct path", second->data->path == "/some/other/path/to/rai.exe");
    mu_assert("third file list item should be created successfully", third  != NULL);
    mu_assert("third file list item should have id of 2", third->id == 2);
    mu_assert("third file list item should have correct name", third->data->name = "feelings");
    mu_assert("third file list item should have correct path", third->data->path == "/trash/feelings");

    return 0;
}

static char * test_item_add() {
    model *MODEL = beforeEach("item_add");

    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    char *filenameTwo = "rai.exe";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *filenameThree = "feelings";
    char *pathThree = "/trash/feelings";

    fileListItem *first = item_create(filename);
    fileListItem *second = item_create(filenameTwo);
    fileListItem *third = item_create(filenameThree);

    item_add(first);
    item_add(second);
    item_add(third);

    mu_assert("first item should be added", MODEL->LIST->first != NULL);
    mu_assert("first item should be added with correct id", MODEL->LIST->first != NULL);
    mu_assert("second item should be accessible from first item", MODEL->LIST->first->next->id == 1 && strcmp(MODEL->LIST->first->next->data->name, "rai.exe") == 0);
    mu_assert("third item should be accessible from second item", MODEL->LIST->first->next->next->id == 2);
    mu_assert("third item should have correct data", strcmp(MODEL->LIST->first->next->next->data->name, "feelings") == 0);
    mu_assert("count should be correct", MODEL->LIST->count == 3);
    mu_assert("MODEL->LIST.last should point to last item", MODEL->LIST->last->id == 2);
    mu_assert("MODEL->LIST.first should point to first item", MODEL->LIST->first->id == 0);
}

static char * test_printFileList() {
    
    model *MODEL = beforeEach("Print File List");

    char *filename = "foo.bar";
    char *path = "/full/path/to/foo.bar";
    char *filenameTwo = "rai.exe";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *filenameThree = "feelings";
    char *pathThree = "/trash/feelings";

    fileListItem *first = item_create(filename);
    fileListItem *second = item_create(filenameTwo);
    fileListItem *third = item_create(filenameThree);

    item_add(first);
    item_add(second);
    item_add(third);

    mu_assert("printFileList should return 0", printFileList(MODEL->LIST) == 0);
    return 0;
}

static char * test_getDirectoryContents()
{
    model *MODEL = beforeEach("getDirectoryContents");
    
    getDirectoryContents("./test_files/");
    
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
    mu_run_test(test_configure);
    mu_run_test(test_getPath);
    mu_run_test(test_getFilename);
    mu_run_test(test_item_create);
    mu_run_test(test_item_add);
    mu_run_test(test_printFileList);
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