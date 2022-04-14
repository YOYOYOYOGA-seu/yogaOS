/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 22:42:24
 * @LastEditTime 2022-04-14 20:28:18
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/lib/list.c
 */

#include "yogaOS/list.h"
#include "yogaOS/types.h"
#include "errno.h"
/**
 * @brief  add a list item to list, ranged by item.value
 * @note  
 * @param {list_t *} list
 * @param {listItem_t *}  item
 * @retval error_t
 */
error_t list_insertList(list_t *list, listItem_t *item)
{
  int i;
  listItem_t *p = list->pFirstItem;
  if(item->value > list->listValueLimit)
    return E_OUT_LIST_VALUE;
  if(item->pListHead == list)   //already in this list
    return ENOERR;
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
      if((item->value <= p->value)||i == list->size)
      {
        item->pNext = p;
        p->pPrevious->pNext = item;
        item->pPrevious = p->pPrevious;
        p->pPrevious = item;

        if(i == 0) //insert as the first item
          list->pFirstItem = item;
        break;
      }
      p = p->pNext;
    }
  }
  
  item->pListHead = list;
  list->size ++;
  return ENOERR;
}

/**
 * @brief  add a list item to list's head(first item)
 * @note  
 * @param {list_t *} list
 * @param {listItem_t *}  item
 * @retval error_t
 */
error_t list_insertHead(list_t *list, listItem_t *item)
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
    item->pNext = p;
    p->pPrevious->pNext = item;
    item->pPrevious = p->pPrevious;
    p->pPrevious = item;
    list->pFirstItem = item;
  }
  item->pListHead = list;
  list->size ++;
  return ENOERR;
}

/**
 * @brief  add a list item to list's tail(last item)
 * @note  
 * @param {list_t *} list
 * @param {listItem_t *}  item
 * @retval error_t
 */
error_t list_insertTail(list_t *list, listItem_t *item)
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
    item->pNext = p;
    p->pPrevious->pNext = item;
    item->pPrevious = p->pPrevious;
    p->pPrevious = item;
  }
  item->pListHead = list;
  list->size ++;
  return ENOERR;
}

/**
 * @brief  remove a list item from it's list
 * @note  
 * @param {listItem_t *}  item
 * @retval error_t
 */

error_t list_removeformList(listItem_t *item)
{
  if(item->pNext == NULL||item->pPrevious == NULL)
    return E_NOT_IN_LIST;
  if(((list_t *)item->pListHead)->size >= 1)
    ((list_t *)item->pListHead)->size--;
  else
    return E_ITEM_NUM_ERR;
  
  if(item->pNext == item)  //can't use pNext = pPrevious, because they equal when num = 1 or 2
  {
    ((list_t *)item->pListHead)->pFirstItem = NULL;
  }
  else
  {
    item->pNext->pPrevious = item->pPrevious;
    item->pPrevious->pNext = item->pNext;
    if(((list_t *)item->pListHead)->pFirstItem == item)
      ((list_t *)item->pListHead)->pFirstItem = item->pNext;
  }
  item->pNext = NULL;
  item->pPrevious = NULL;
  item->pListHead = NULL;
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void list_initList(list_t *list, uint32_t listMaxValue)
{
  list->size = 0;
  list->listValueLimit = listMaxValue;
  list->pFirstItem = NULL;
}