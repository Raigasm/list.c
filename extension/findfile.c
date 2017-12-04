#include "debugprint.h"
#include "findfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelist.h"
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

// traverses a directory on the user's filesystem and stores it in a specified FileList
fileList *directory_get(char *path)
{
  
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
  MODEL->TREE->root = (node *) 0;

  return MODEL;
}

// Wraps file data in a node object (without any references to parents etc)
node *node_create(char *input)
{
  return 0;
}


// compare a new node 'b' with an existing node 'a'
// if 'b' is less then returns -1 
// if 'b' is more then returns 1
// if equal then returns 0
int node_compare(node *a, node *b){
  return strcmp(a->path, b->path);
}

/** inserts a node in the right position in a tree
 *  sets parent/children appropriately for the new node
 *  updates children for the parent node, if any
 *  updates the node count 
 *  NB: returns 0 if unsuccessful, 
 **/
int node_insert(node *input, binarySearchTree *output)
{
  // check if root exists
  if (output->root == (node *) 0){
    // if root doesn't exist, create root
    output->root = input;
  } else {
    bool inserted = false;
    node *parent = output->root;
    
    while(!inserted){
      int comparison = node_compare(parent, input);
      if (comparison < 0){ // new node is lesser
        if (parent->leftChild == (node *) 0){
          input->parent = parent;
          parent->leftChild = input;
          inserted = true;
        } else {
          parent = parent->leftChild;
        }
      } else if (comparison > 0){ // new node is greater
        if (parent->rightChild == (node *) 0)
        {
          input->parent = parent;
          parent->rightChild = input;
          inserted = true;
        }
        else
        {
          parent = parent->rightChild;
        }
      } else {
        DEBUG_PRINT("duplicate file detected, discarding\n.");
      }
    }
  }

  output->size++;
    return 0;
}

// prints the contents of the tree to stdout
// returns 0 if successful, otherwise 1
int tree_print(binarySearchTree *input)
{
  return 0;
}

// transforms a FileList into a binary search tree
binarySearchTree *tree_create(fileList *input)
{
  return 0;
}

// memory cleanup
// returns 0 if successful. Burns down your home if unsuccessful.
int tree_destroy()
{
  return 0;
}

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results in a FileList
fileList *tree_search(char *input)
{
  return 0;
}

