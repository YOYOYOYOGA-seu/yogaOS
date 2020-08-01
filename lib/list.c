/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 22:42:24
 * @LastEditTime 2020-08-01 08:16:58
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/list.c
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
  if(item->pOwnList == list)   //already in this list
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
      if((item->value <= p->value)||i == list->numberOfItem)
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
  
  item->pOwnList = list;
  list->numberOfItem ++;
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
  item->pOwnList = list;
  list->numberOfItem ++;
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
  item->pOwnList = list;
  list->numberOfItem ++;
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
  if(((list_t *)item->pOwnList)->numberOfItem >= 1)
    ((list_t *)item->pOwnList)->numberOfItem--;
  else
    return E_ITEM_NUM_ERR;
  
  if(item->pNext == item)  //can't use pNext = pPrevious, because they equal when num = 1 or 2
  {
    ((list_t *)item->pOwnList)->pFirstItem = NULL;
  }
  else
  {
    item->pNext->pPrevious = item->pPrevious;
    item->pPrevious->pNext = item->pNext;
    if(((list_t *)item->pOwnList)->pFirstItem == item)
      ((list_t *)item->pOwnList)->pFirstItem = item->pNext;
  }
  item->pNext = NULL;
  item->pPrevious = NULL;
  item->pOwnList = NULL;
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
  list->numberOfItem = 0;
  list->listValueLimit = listMaxValue;
  list->pFirstItem = NULL;
}