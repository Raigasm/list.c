#include "debugprint.h"
#include "findfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "tinydir.h"

void copyString(char *input, char *output)
{
  while (*input != '\0')
  {
    *output = *input;
    input++;
    output++;
  }
  // terminate string with null character
  *output = '\0';
}

// returns true if this node is the root node, otherwise false;
bool isRoot(node *input)
{
  if (input->parent != NULL) {
    return false;
  } else {
    return true;
  }
}

// returns true if this node is a leaf node, otherwise false
bool isLeaf(node *input)
{
  if (input->leftChild == NULL && input->rightChild == NULL) {
    return true;
  } else {
    return false;
  }
}

// returns the filename of a specific file
char *getFilename(fileInfo *input, char *output)
{
  copyString(input->name, output);
}

// gets the full path of a specific file
char *getPath(fileInfo *input, char *output){
  copyString(input->path, output);
}

// traverses a directory on the user's filesystem and stores it in a specified FileList
fileList *getDirectoryContents(char *path, fileList *output)
{
  tinydir_dir dir;
  tinydir_open(&dir, "/path/to/dir");

  while (dir.has_next)
  {
    tinydir_file file;
    tinydir_readfile(&dir, &file);

    printf("%s", file.name);
    if (file.is_dir)
    {
      printf("/");
    }
    printf("\n");

    tinydir_next(&dir);
  }

  tinydir_close(&dir);
}


// prints usage instructions to stdout
void printInstructions(void)
{
  printf("Findfile: no query specified!\nPlease specify a filename to find, and a directory to look within (optional)\n\nExample: findfile 'Mozart' ~/Downloads/Music\n");
}

// validates/parses command line arguments and sets up the configuration store (CONFIG)
// returns 0 if input is valid and configuration successful, otherwise 1
int parseInput(char *input)
{
  return 0; 
}

// 
fileListItem *createFileListItem(char *name, char *path) {
  return 0;
}

fileList *addFileListItem(fileListItem *input, fileList *output){
  return 0;
}

    // Wraps file data in a node object (without any references to parents etc)
    node *createNode(fileInfo *input, node *output)
{
  return 0;  
}

/** inserts a node in the right position in a tree
 *  sets parent/children appropriately for the new node
 *  updates children for the parent node, if any
 *  updates the node count 
 *  NB: returns 0 if unsuccessful, 
 **/
int insertNode(node *input, binarySearchTree *output)
{
  return 0;
}

// prints the contents of the tree to stdout
// returns 0 if successful, otherwise 1
int printTree(binarySearchTree *input)
{
  return 0;
}

// removes a node from the tree, retaining the correct order/structure
int deleteNode(node *toDelete, binarySearchTree *tree)
{
  return 0;
}

// transforms a FileList into a binary search tree
binarySearchTree *makeTree(fileList *input, binarySearchTree *output)
{
  return 0;
}

// memory cleanup
// returns 0 if successful. Burns down your home if unsuccessful.
int destroyTree(binarySearchTree *toDelete)
{
  return 0;
}

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results in a FileList
fileList *searchFor(char *input, binarySearchTree *tree, fileList *output)
{
  return 0;
}

// prints a file list to stdout
// returns 0 if successful, otherwise 1
int printFileList(fileList *input){
  return 0;  
}

