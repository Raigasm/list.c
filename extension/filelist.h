#include <stdbool.h>
#ifndef FILELIST_H_
#define FILELIST_H_

// represents each file
typedef struct FileInfo
{
  char *name; // filename with extension
  char *path; // full file path
} fileInfo;

// item in list of files
typedef struct FileListItem
{
  int id; // starts at 0
  struct FileInfo *data;
  struct FileListItem *next; // reference to next item
} fileListItem;

// a single-linked list of files
typedef struct FileList
{
  int count;                  // same as (last.id + 1)
  struct FileListItem *first; // should be a reference to item with id 0
  struct FileListItem *last;  // should be a reference to item with id (count - 1)
} fileList;

// item functions
fileListItem *item_create(char *name);
fileListItem *item_add(fileListItem *input);
void *item_remove(int id);

// list functions
void list_print(fileList *input);
void list_last(fileList *input);
void list_first(fileList *input);
void list_count(fileList *input);


#endif