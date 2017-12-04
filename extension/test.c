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
    char *testQuery = "txt";
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
    char *path = "/full/path/to/foo.bar";

    node *root = malloc(sizeof(node));
    root->path = path;
    root->leftChild = NULL;
    root->rightChild = NULL;
    root->parent = NULL; 

    node *notRoot = malloc(sizeof(node));
    notRoot->path = path;
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
    char *path = "/full/path/to/foo.bar";

    node *leaf = malloc(sizeof(node));
    node *notLeaf = malloc(sizeof(node));
    node *anotherLeaf = malloc(sizeof(node));

    leaf->path = path;
    leaf->leftChild = NULL;
    leaf->rightChild = NULL;
    leaf->parent = notLeaf;

 
    anotherLeaf->path = path;
    anotherLeaf->leftChild = NULL;
    anotherLeaf->rightChild = NULL;
    anotherLeaf->parent = notLeaf;


    notLeaf->path = path;
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
    mu_assert("TREE should be set properly", MODEL->TREE != NULL);
    mu_assert("COUNT should be set properly", MODEL->COUNT == 0);
    
    return 0;
}

static char * test_item_create() {
    model *MODEL = beforeEach("item_create");

    char *path = "/full/path/to/foo.bar";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *pathThree = "/trash/feelings";

    fileListItem *first = item_create(0, path);
    fileListItem *second = item_create(1, pathTwo);
    fileListItem *third = item_create(2, pathThree);

    mu_assert("file list item should be created successfully", first != NULL);
    mu_assert("first file list item should have id of 0", first->id == 0);
    mu_assert("first file list item should have correct path", first->path == "/full/path/to/foo.bar");
    mu_assert("second file list item should be created successfully", second != NULL);
    mu_assert("second file list item should have id of 1", second->id == 1);
    mu_assert("second file list item should have correct path", second->path == "/some/other/path/to/rai.exe");
    mu_assert("third file list item should be created successfully", third  != NULL);
    mu_assert("third file list item should have id of 2", third->id == 2);
    mu_assert("third file list item should have correct path", third->path == "/trash/feelings");

    return 0;
}

static char * test_item_add() {
    model *MODEL = beforeEach("item_add");

    char *path = "/full/path/to/foo.bar";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *pathThree = "/trash/feelings";

    fileListItem *first = item_create(0, path);
    fileListItem *second = item_create(1, pathTwo);
    fileListItem *third = item_create(2, pathThree);

    item_add(first, MODEL->LIST);
    item_add(second, MODEL->LIST);
    item_add(third, MODEL->LIST);

    mu_assert("first item should be added", MODEL->LIST->first != NULL);
    mu_assert("first item should be added with correct id", MODEL->LIST->first != NULL);
    mu_assert("second item should be accessible from first item", MODEL->LIST->first->next->id == 1 && strcmp(MODEL->LIST->first->next->path, "/some/other/path/to/rai.exe") == 0);
    mu_assert("third item should be accessible from second item", MODEL->LIST->first->next->next->id == 2);
    mu_assert("third item should have correct data", strcmp(MODEL->LIST->first->next->next->path, "/trash/feelings") == 0);
    mu_assert("count should be correct", MODEL->LIST->count == 3);
    mu_assert("MODEL->LIST.first should point to first item", MODEL->LIST->first->id == 0);
}

static char * test_list_print() {
    
    model *MODEL = beforeEach("Print File List");

    char *path = "/full/path/to/foo.bar";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *pathThree = "/trash/feelings";

    fileListItem *first = item_create(0, path);
    fileListItem *second = item_create(1, pathTwo);
    fileListItem *third = item_create(2, pathThree);

    item_add(first, MODEL->LIST);
    item_add(second, MODEL->LIST);
    item_add(third, MODEL->LIST);

    char *result = list_print(MODEL->LIST);
    mu_assert("list_print should return the correct string", sameString(result, "Files:\n/full/path/to/foo.bar\n/some/other/path/to/rai.exe\n/trash/feelings\n"));
    return 0;
}

static char *test_list_last()
{

    model *MODEL = beforeEach("list_last");

    char *path = "/full/path/to/foo.bar";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *pathThree = "/trash/feelings";

    fileListItem* result;

    fileListItem *first = item_create(0, path);
    fileListItem *second = item_create(1, pathTwo);
    first->next = second;
    fileListItem *third = item_create(2, pathThree);
    second->next = third;
    third->next = (fileListItem *) 0;

    fileList *testList = malloc(sizeof(fileList));
    testList->first = first;
    testList->count = 3;

    result = list_last(testList);

    mu_assert("last file should return 3rd (test: id)", result->id = 2);
    mu_assert("last file should return 3rd (test: path)", strcmp(result->path, "/trash/feelings") == 0);
    return 0;
}

static char *test_list_first()
{

    model *MODEL = beforeEach("list_first");

    char *path = "/full/path/to/foo.bar";
    char *pathTwo = "/some/other/path/to/rai.exe";
    char *pathThree = "/trash/feelings";

    fileListItem *result;

    fileListItem *first = item_create(0, path);
    fileListItem *second = item_create(1, pathTwo);
    first->next = second;
    fileListItem *third = item_create(2, pathThree);
    second->next = third;
    third->next = (fileListItem *) 0;

    fileList *testList = malloc(sizeof(fileList));
    testList->first = first;
    testList->count = 3;

    result = list_first(testList);

    DEBUG_PRINT("result = %i (%s)\n", result->id, result->path);
    mu_assert("last file should return 1st (test: id)", result->id == 0);
    return 0;
}


static char * test_node_compare() {
    node *a = malloc(sizeof(node));
    node *b = malloc(sizeof(node));
    node *c = malloc(sizeof(node));

    a->path = "alpha";
    b->path = "bravo";
    c->path = "charlie";

    DEBUG_PRINT("a/b comparison = %i\n", node_compare(a,b));

    mu_assert("compare should return negative for greater b", node_compare(a,b) < 0);
    mu_assert("compare should return positive for lesser b", node_compare(b,a) > 0);
    mu_assert("compare should return positive for lesser b (again)", node_compare(c,a) > 0);
    mu_assert("compare should return positive for greater b (again #2)", node_compare(c,b) > 0);
    mu_assert("compare should return 0 if equal", node_compare(a,a) == 0);
}

static char * test_directory_get()
{
    model *MODEL = beforeEach("getDirectoryContents");
    binarySearchTree *tree = MODEL->TREE;
    
    directory_get("./test_files/", MODEL->LIST);
    
    mu_assert("getting directory updates filelist with correct number of files", MODEL->LIST->count > 0);
    return 0;
}


static char * test_parseInput()
{
    printf("running test for parseInput\n");

    char *arg_one = "findfile";
    char *arg_two = "txt";
    char *arg_three = "./test_files";

    char *all_arguments[255];
    
    all_arguments[0] = arg_one;
    mu_assert("parseInput returns 1 if invalid number of arguments", parseInput(1, all_arguments) == 1);
    all_arguments[1] = arg_two;
    mu_assert("parseInput returns 0 if only query specified", parseInput(2, all_arguments) == 0);
    all_arguments[2] = arg_three;
    mu_assert("parseInput returns 0 if query + location specified", parseInput(3, all_arguments) == 0);
    return 0;
}

static char * test_node_create()
{
    model *MODEL = beforeEach("node_create");

    char *path_one = "/foo/bar";
    char *path_two = "/i/wish/she/felt/the/same/way";
    char *path_three = "/tree/to/the/future";

    node *node_one = node_create(path_one);
    node *node_two = node_create(path_two);
    node *node_three = node_create(path_three);

    mu_assert("node_one should be created successfully", sameString(node_one->path, "/foo/bar"));
    mu_assert("node_two should be created successfully", sameString(node_two->path, "/i/wish/she/felt/the/same/way"));
    mu_assert("node_three should be created successfully", sameString(node_three->path, "/tree/to/the/future"));

    return 0;
}

static char * test_node_insert()
{
    model *MODEL = beforeEach("insert node");
    binarySearchTree *tree = MODEL->TREE;

    char *path_one = "beta";
    char *path_two = "alpha";
    char *path_three = "gamma";

    node *node_one = node_create(path_one);
    node *node_two = node_create(path_two);
    node *node_three = node_create(path_three);

    mu_assert("size starts out at 0", MODEL->TREE->size == 0);
    node_insert(node_one, MODEL->TREE);
    mu_assert("size increases to 1", MODEL->TREE->size == 1);
    node_insert(node_two, MODEL->TREE);
    mu_assert("size increases to 2", MODEL->TREE->size == 2);
    node_insert(node_three, MODEL->TREE);
    mu_assert("size increases to 3", MODEL->TREE->size == 3);

    mu_assert("size updated to reflect inserted nodes", MODEL->TREE->size == 3);
    
    return 0;
}

static char * test_tree_create()
{
    mu_assert("test_tree_create implemented", true);
    return 0;
}

static char * test_destroyTree()
{
    printf("running test for destroyTree\n");
    mu_assert("test_destroyTree not yet implemented", false);
    return 0;
}

static char * test_tree_search()
{
    model *MODEL = beforeEach("tree_search");

    directory_get(MODEL->DIRECTORY, MODEL->LIST);
    MODEL->TREE = tree_create(MODEL->LIST);

    fileList *results = tree_search(MODEL->QUERY);
    
    list_print(results);

    mu_assert("right number of files found", results->count > 0);
    return 0;
}

static char * all_tests () {
    mu_run_test(test_copyString);
    mu_run_test(test_isRoot);
    mu_run_test(test_isLeaf);
    mu_run_test(test_configure);
    mu_run_test(test_item_create);
    mu_run_test(test_list_last);
    mu_run_test(test_list_first);
    mu_run_test(test_item_add);
    mu_run_test(test_list_print);
    mu_run_test(test_node_compare);
    mu_run_test(test_node_create);
    mu_run_test(test_node_insert);
    mu_run_test(test_parseInput);
    mu_run_test(test_directory_get);
    mu_run_test(test_tree_create);
    mu_run_test(test_tree_search);
    mu_run_test(test_destroyTree);
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