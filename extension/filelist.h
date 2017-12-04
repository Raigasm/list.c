#include <stdbool.h>
#ifndef FILELIST_H_
#define FILELIST_H_

// item in list of files
typedef struct FileListItem
{
  int id; // starts at 0
  char *path;
  struct FileListItem *next; // reference to next item
} fileListItem;

// a single-linked list of files
typedef struct FileList
{
  int count;                  // same as (last.id + 1)
  struct FileListItem *first; // should be a reference to item with id 0
} fileList;

// item functions
fileListItem *item_create(int id, char *name);
fileListItem *item_add(fileListItem *input, fileList *output);

// list functions
char *list_print(fileList *input);
fileListItem *list_last(fileList *input);
fileListItem *list_first(fileList *input);
int list_count(fileList *input);


#endif