#include "debugprint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelist.h"

fileListItem *item_create(int id, char *name)
{
  fileListItem *output = (fileListItem *) malloc(sizeof(fileListItem));
  output->path = name;
  output->id = id;
  output->next = (fileListItem *) 0;
  return output;
}

fileListItem *item_add(fileListItem *input)
{
  DEBUG_PRINT("not yet implemented :X\n");
}

void *item_remove(int id)
{
  DEBUG_PRINT("not yet implemented :X\n");
}

// list functions
void list_print(fileList *input)
{
  DEBUG_PRINT("not yet implemented :X\n");
}

fileListItem *list_last(fileList *input)
{
  fileListItem *result = input->first;
  
  while(result->next != (fileListItem *) 0)
  {
    result = result->next;
  }  

  DEBUG_PRINT("list_last: last file id %i (%s)\n", result->id, result->path);
  
  return result;
}

fileListItem *list_first(fileList *input)
{
  DEBUG_PRINT("not yet implemented :X\n");
}

int list_count(fileList *input)
{
  DEBUG_PRINT("not yet implemented :X\n");
}