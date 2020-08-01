/*
 * @Author Shi Zhangkun
 * @Date 2020-02-21 20:59:03
 * @LastEditTime 2020-08-01 08:16:06
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/yogaOS/list.h
 */
#ifndef __LIST_H
#define __LIST_H

#include "yogaOS/types.h"
/* ------------------------ type define --------------------------- */
/* double linked  list */
typedef struct listItem{
  unsigned int value;
  struct listItem * pNext;
  struct listItem * pPrevious;
  void * pOwner;
  void * pOwnList;
}listItem_t;
/* double linked  list */
typedef struct {
  unsigned int numberOfItem;
  unsigned int listValueLimit;
  listItem_t *pFirstItem;

}list_t; 
/*simple single linked list */

typedef struct miniListItem{
  unsigned int value;
  struct miniListItem * pNext;
  void * pOwner;
}miniListItem_t;


typedef struct {
  unsigned int numberOfItem;
  miniListItem_t *pFirstItem;
}miniList_t;


void list_initList(list_t *list, uint32_t listMaxValue);
error_t list_insertList(list_t *list, listItem_t *item);
error_t list_insertHead(list_t *list, listItem_t *item);
error_t list_insertTail(list_t *list, listItem_t *item);
error_t list_removeformList(listItem_t *item);

#endif
