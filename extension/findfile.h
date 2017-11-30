#include <stdbool.h>
#ifndef FINDFILE_H_
#define FINDFILE_H_

// represents each file
typedef struct NodeData 
{
  char *filename; // filename with extension
  char *path;     // full file path
} nodeData;

// wrapper for file data so that it can be used in the binary search tree
typedef struct Node 
{
  struct NodeData data; // contains the filename and path
  struct Node *leftChild; // reference to left child, if any 
  struct Node *rightChild; // reference to right child, if any
  struct Node *parent; 
} node;

// a binary search tree containing files in the search directory
typedef struct BinarySearchTree 
{
  struct Node *root; // the root node 
  int size; // number of nodes in the tree
} binarySearchTree;

// a linked list of search results
typedef struct SearchResults 
{
  int numberOfResults;
  struct Node *first;
  struct Node *last;
} searchResults;

// configuration generated based off run parameters
struct CONFIG
{
    int searchAlgorithm; // 0 = Binary Search, 1 = ?
    char *searchIn; // path to search in 
};

// returns true if this node is the root node, otherwise false;
bool isRoot(Node); 

// returns true if this node is a leaf node, otherwise false
bool isLeaf(Node); 

// returns the filename of a specific node 
char *getFilename(Node);

// gets the full path of a specific node
char *getPath(Node); 

// traverses a directory on the user's filesystem and returns a list of filenames
void getDirectoryContents (void); //TODO: fix signature for getDirectoryContents

// prints usage instructions to stdout
void printInstructions (void); //TODO: fix signature for printInstructions

// validates/parses command line arguments and sets up the configuration store (CONFIG) 
void parseInput (void); //TODO: fix signature for parseInput

// inserts a node in the right position in the tree
void insertNode (void); //TODO: fix signature for insertNode

// prints the contents of the tree
void printTree (void); //TODO: fix signature for printTree

// removes a node from the tree, retaining the correct order/structure
void deleteNode (void); //TODO: fix signature for deleteNode

// turns a list of files into a binary search tree
void makeTree (void); //TODO: fix signature for makeTree

// memory cleanup
void destroyTree (void); //TODO: fix signature for destroyTree#

// traverses the tree to find a given search term (TODO: case insensitive, TODO: partial matches accepted?), storing the results as a searchResult
void searchFor (void); //TODO: fix signature for searchFor

// prints results found
void printResults (void); //TODO: fix signature for printResults

#endif