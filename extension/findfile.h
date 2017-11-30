#include <stdbool.h>
#ifndef FINDFILE_H_
#define FINDFILE_H_

// represents each file
typedef struct FileInfo
{
  char *name; // filename with extension
  char *path;     // full file path
} fileInfo;

// wrapper for file data so that it can be used in the binary search tree
typedef struct Node 
{
  struct FileInfo *data; // contains the filename and path
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

// a linked list of files
typedef struct FileList 
{
  int count;
  struct Node *first;
  struct Node *last;
} fileList;

// configuration generated based off run parameters
struct CONFIG
{
    int searchAlgorithm; // 0 = Binary Search, 1 = ?
    char *searchIn; // path to search in 
};

// returns true if this node is the root node, otherwise false;
bool isRoot(node *input); 

// returns true if this node is a leaf node, otherwise false
bool isLeaf(node *input); 

// returns the filename of a specific file 
char *getFilename(fileInfo *input);

// gets the full path of a specific file
char *getPath(fileInfo *input); 

// traverses a directory on the user's filesystem and stores it in a specified FileList
fileList *getDirectoryContents (char *directory, fileList *output);

// prints usage instructions to stdout
void printInstructions (void); 

// validates/parses command line arguments and sets up the configuration store (CONFIG) 
// returns 0 if input is valid and configuration successful, otherwise 1
int parseInput (char *input); 

// Wraps file data in a node object (without any references to parents etc)
node *createNode(fileInfo *input);

/** inserts a node in the right position in a tree
 *  sets parent/children appropriately for the new node
 *  updates children for the parent node, if any
 *  updates the node count 
 *  NB: returns 0 if unsuccessful, 
 **/
int insertNode (node *input, binarySearchTree *output); 

// prints the contents of the tree to stdout
// returns 0 if successful, otherwise 1
int printTree (binarySearchTree *input); 

// removes a node from the tree, retaining the correct order/structure
int deleteNode (node *toDelete, binarySearchTree *tree);

// transforms a FileList into a binary search tree
binarySearchTree *makeTree (fileList *input, binarySearchTree *output); 

// memory cleanup
// returns 0 if successful. Burns down your home if unsuccessful.
int destroyTree (binarySearchTree *toDelete);

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results in a FileList
fileList *searchFor (char *input, binarySearchTree *tree, fileList *output);

// prints a file list to stdout
// returns 0 if successful, otherwise 1
int printFileList (fileList *input); 

#endif