#include <stdbool.h>
#include "filelist.h"
#ifndef FINDFILE_H_
#define FINDFILE_H_

// wrapper for file data so that it can be used in the binary search tree
typedef struct Node 
{
  char *path; // path + file name
  struct Node *leftChild; // reference to left child, if any 
  struct Node *rightChild; // reference to right child, if any
  struct Node *parent; // reference to the parent node, if not the root node.
} node;

// a binary search tree containing files in the search directory
typedef struct BinarySearchTree 
{
  struct Node *root; // the root node 
  int size; // number of nodes in the tree
} binarySearchTree;

// configuration / model state object generated based off run parameters
typedef struct Model
{
    int ALGORITHM; // 0 = Binary Search, 1 = ?
    char *DIRECTORY; // path to search in, default is cwd 
    struct FileList *LIST; 
    struct BinarySearchTree *TREE;// generated 
    int COUNT;
    char *QUERY; // file to search for
} model;

// copies a string from input to output (I forgot strcpy existed)
void copyString(char *input, char *output);

// returns true if this node is the root node, otherwise false;
bool isRoot(node *input);

// returns true if this node is a leaf node, otherwise false
bool isLeaf(node *input); 

// returns the filename of a specific file 
char *getFilename(char *input, char *output);

// gets the full path of a specific file
char *getPath(char *input, char *output);

// initializes model 
model *configure (char *query, char *directory);

// traverses a directory on the user's filesystem and stores it in a specified FileList
fileList *directory_get (char *directory, fileList *output);

// prints usage instructions to stdout
void printInstructions (void);

// validates/parses command line arguments and sets up the configuration store (CONFIG) 
// returns 0 if input is valid and configuration successful, otherwise 1
int parseInput (int argc, char *argv[]); 

// Wraps file data in a node object (without any references to parents etc)
node *node_create(char *input);

/** 
 *  inserts a node in the right position in a tree
 *  sets parent/children appropriately for the new node
 *  updates children for the parent node, if any
 *  updates the node count 
 *  NB: returns 0 if unsuccessful, 
 **/
int node_insert(node *input, binarySearchTree *output);

// removes a node from the tree, retaining the correct order/structure
int node_delete (node *toDelete);

// transforms a FileList into a binary search tree
binarySearchTree *tree_create (fileList *input);

// memory cleanup
// returns 0 if successful. Burns down your home if unsuccessful.
int tree_destroy ();

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results in a FileList
fileList *tree_search (char *input);

#endif