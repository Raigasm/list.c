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
fileList *directory_get(char *path, fileList *output)
{
  tinydir_dir dir;
  int i;
  tinydir_open_sorted(&dir, path);

  DEBUG_PRINT("Found %i files in directory %s\n", dir.n_files, path);
  for (i = 0; i < dir.n_files; i++)
  {
    tinydir_file file;
    tinydir_readfile_n(&dir, &file, i);

    fileListItem *newest = item_create(i, file.name);
    item_add(newest, output);
  }

  tinydir_close(&dir);
}


// prints usage instructions to stdout
void printInstructions(void)
{
  printf("Findfile: no query specified!\nPlease specify a filename to find, and a directory to look within (optional)\n\nExample: findfile 'Mozart' ~/Downloads/Music\n");
}

// validates/parses command line arguments and sets up the configuration store (CONFIG)
// returns 0 if successful, 1 if error
int parseInput(int number_of_arg, char *all_args[])
{
  char *query; 
  char *directory;
  
  DEBUG_PRINT("parseInput: %i arguments\n", number_of_arg);
  
  if(number_of_arg == 1){
    printInstructions();
    return 1;
  }
  
  if (number_of_arg == 2 || number_of_arg == 3){
    DEBUG_PRINT("correct number of arguments supplied\n");
    query = all_args[1];
    if (number_of_arg == 2) {
      directory = "./";
    } else {
      directory = all_args[2];
    }
    DEBUG_PRINT("searching for %s in %s", query, directory);
    configure(query, directory);
    return 0;
  }
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
  node *output = (node *) malloc(sizeof(node));
  output->path = input;
  return output;
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
        inserted = true;
      }
    }
  }

  output->size++;
  return 0;
}

// transforms a FileList into a binary search tree
binarySearchTree *tree_create(fileList *input)
{
  binarySearchTree *output = malloc(sizeof(binarySearchTree));

  fileListItem *current = input->first;

  while(current != (fileListItem *) 0){
    node *newNode = node_create(current->path);
    node_insert(newNode, output);
    current = current->next;
  }

  return output;
}

// memory cleanup
// returns 0 if successful. Burns down your home if unsuccessful.
int tree_destroy()
{
  return 0;
}

node *search (node *root, char *query){
  // Base Cases: root is null or key is present at root
  if (root == NULL || strcmp(query, root->path) == 0){
    return root;
  }

  // Key is greater than root's key
  if (node_compare(root->path, path) > 0)
    return search(root->rightChild, path);

  // path is smaller than root's path
  return search(root->leftChild, path);
}

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results in a FileList
node *tree_search(binarySearchTree *source, char *query)
{
  node *result;
  search(source->root, query);  
  return result;
}

