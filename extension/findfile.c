#include "debugprint.h"
#include "findfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "tinydir.h"

model *MODEL;

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
  return output;
}

// gets the full path of a specific file
char *getPath(fileInfo *input, char *output){
  copyString(input->path, output);
  return output;
}

// traverses a directory on the user's filesystem and stores it in a specified FileList
fileList *getDirectoryContents(char *path)
{
  DEBUG_PRINT("not yet implemented\n");

  // from https://github.com/cxong/tinydir
  tinydir_dir dir;
  int i;
  tinydir_open_sorted(&dir, path);

  if (dir.n_files == 0)
  {
    printf("NO FILES IN DIRECTORY SPECIFIED!\n");
  }

  for (i = 0; i < dir.n_files; i++)
  {
    tinydir_file file;
    tinydir_readfile_n(&dir, &file, i);

    if (file.is_dir)
    {
      printf("/");
    }

    if (!file.is_dir)
    {
      printf("found file %s (%s)\n", file.name, file.path);
      fileListItem *item = createFileListItem(file.name, file.path);
      addFileListItem(item);
    }
  }

  tinydir_close(&dir);



  printFileList(MODEL->LIST);
  
  return MODEL->LIST;
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

// initializes model
model *configure(char *query, char *directory) {
  MODEL = (model *) malloc(sizeof(model));
  MODEL->COUNT = 0;
  MODEL->DIRECTORY = directory;
  MODEL->ALGORITHM = 0;
  MODEL->LIST = (fileList *) malloc(sizeof(fileList));
  MODEL->LIST->count = 0;
  MODEL->TREE = (binarySearchTree *) malloc(sizeof(binarySearchTree));
  MODEL->TREE->size = 0;
  
  // DEBUG_PRINT("initialized model for %s\n", directory);

  return MODEL;
}

fileListItem *createFileListItem(char *name, char *path)
{
  fileListItem *result = (fileListItem *) malloc(sizeof(fileListItem));
  fileInfo *data = (fileInfo *) malloc(sizeof(fileInfo));
  data->name = name;
  data->path = path;
  result->id = MODEL->COUNT++;
  result->data = data;
  result->next = 0;
  printf("created %s (%s)\n", data->name, data->path);
  return result;
}

fileListItem *getLastFile(){
  DEBUG_PRINT("finding last file\n");
  return MODEL->LIST->last;
}

fileList *addFileListItem(fileListItem *input){
  
  DEBUG_PRINT("adding %s\n", input->data->name);
  
  if (MODEL->LIST->count == 0){
    DEBUG_PRINT("setting first file\n");
    MODEL->LIST->first = input;
    MODEL->LIST->last = input;
  } else {
    DEBUG_PRINT("adding to existing list.\n");
    fileListItem *last = getLastFile();
    DEBUG_PRINT("the last file was %s (id: %i)\n", last->data->name, last->id);
    last->next = input;
    MODEL->LIST->last = input;
  }

  
  MODEL->LIST->count++;

  return MODEL->LIST;
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
int insertNode(node *input)
{
  return 0;
}

// prints the contents of the tree to stdout
// returns 0 if successful, otherwise 1
int printTree()
{
  return 0;
}

// removes a node from the tree, retaining the correct order/structure
int deleteNode(node *toDelete)
{
  return 0;
}

// transforms a FileList into a binary search tree
binarySearchTree *makeTree(fileList *input)
{
  return 0;
}

// memory cleanup
// returns 0 if successful. Burns down your home if unsuccessful.
int destroyTree()
{
  return 0;
}

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results in a FileList
fileList *searchFor(char *input)
{
  return 0;
}

// prints a file list to stdout
// returns 0 if successful, otherwise 1
int printFileList(fileList *input){
  int filesPrinted = 0;

  printf("-----------------\nFiles (%i in total):\n-----------------\n", input->count);
  fileListItem *currentFile = MODEL->LIST->first;
  
  for (size_t i = 1; i <= MODEL->COUNT; i++)
  {
    printf("%i - %s\n", currentFile->id + 1, currentFile->data->name);
    filesPrinted++;
    currentFile = currentFile->next;
  }

  if (filesPrinted > 0){
    return 0;
  } else {
    return 1;
  } 
}

