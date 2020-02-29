/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 22:42:24
 * @LastEditTime 2020-02-28 23:36:00
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/list.c
 */

#include "list.h"
#include "type.h"
#include "errno.h"

error_t list_insertList(list_t *list, listItem_t *item)
{
  int i;
  listItem_t *p = list->pFirstItem;
  if(item->value > list->listValueLimit)
    return E_OUT_LIST_VALUE;
  if(p == NULL)
  {
    list->pFirstItem = item;
    item->pNext = item;
    item->pPrevious = item;
  }
  else
  {
    for(i = 0; ; i++)
    {
      if((item->value <= p->value)||i == list->numberOfItem)
      {
        item->pNext = p;
        p->pPrevious->pNext = item;
        item->pPrevious = p->pPrevious;
        p->pPrevious = item;
        break;
      }
      p = p->pNext;
    }
  }
  
 
  list->numberOfItem ++;
  return ENOERR;
}

void list_initList(list_t *list, uint32_t listMaxValue)
{
  list->numberOfItem = 0;
  list->listValueLimit = listMaxValue;
  list->pFirstItem = NULL;
}