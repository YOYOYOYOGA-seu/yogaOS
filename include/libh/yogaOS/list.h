/*
 * @Author Shi Zhangkun
 * @Date 2020-02-21 20:59:03
 * @LastEditTime 2020-08-01 07:48:38
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

typedef struct {
  unsigned int numberOfItem;
  unsigned int listValueLimit;
  listItem_t *pFirstItem;

}list_t; 

/*simple single linked list */

typedef struct sigListItem_t{
  union {
    void * pOwner;
    unsigned int value;
  };
  struct sigListItem_t * pNext;
  
}sigListItem_t_t;


typedef struct {
  unsigned int numberOfItem;
  sigListItem_t_t *pFirstItem;
}sigList_t;

/** A mini list creat define, this define can creat a struct obj that 
 * using the specified input type, so it can easily embed into any data
 * struct and can opreate the struct as a list item.
 * 
 * for example :
 *         miniList_t(type) listHead;
 * 
 *         struct listObj{
 *            ...
 *            miniList_t(srtuct Obj) lp;
 *            ...
 *        };
 */

#define miniList_t(type)   struct{ unsigned int value; type * firstItem; }
#define miniListItem_t(type)   struct{ type * pNext; type * pPrevious; }
/**
 * @brief  
 * @note  
 * @param {miniList_t} head : : list head
 * @retval none
 */
#define miniList_init(head){ \
          head.firstItem = 0; \
          head.value = 0; \
        }
/**
 * @brief  insert a item to a mini list
 * @note  don't support circle, it mean's the firstItem.pPrevious and lastItem.pNext are both NULL
 * @param {miniList_t} head : list head 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertHead(head,pItem,__listItemObjName) {   \
          if(head.firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = head.firstItem;  \
            (pItem)->__listItemObjName.pPrevious = head.firstItem->__listItemObjName.pPrevious; \
            head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            head.firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
          } \
          head.firstItem = pItem; \
          head.value++;   \
        }
/**
 * @brief  insert a item to a mini list
 * @note  don't support circle, it mean's the firstItem.pPrevious and lastItem.pNext are both NULL
 * @param {miniList_t} head : list head 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertTail(head,pItem,__listItemObjName) {   \
          if(head.firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = head.firstItem;  \
            (pItem)->__listItemObjName.pPrevious = head.firstItem->__listItemObjName.pPrevious; \
            head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            head.firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
             head.firstItem = pItem; \
          } \
          head.value++;   \
        }
/**
 * @brief  pop the first item in this list
 * @note  
 * @param {miniList_t} head : list head 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopHead(head, __listItemObjName) head.firstItem;  \
        {   \
          if(head.value == 0||head.firstItem == 0) \
            goto POP_END; \
          head.value--; \
          if(head.value == 0){   \
            head.firstItem->__listItemObjName.pNext = 0;  \
            head.firstItem->__listItemObjName.pPrevious = 0;  \
            head.firstItem = 0; \
          }else{ \
            head.firstItem->__listItemObjName.pNext->__listItemObjName.pPrevious =  head.firstItem->__listItemObjName.pPrevious;  \
            head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = head.firstItem->__listItemObjName.pNext; \
            void* p =  head.firstItem->__listItemObjName.pNext; \
            head.firstItem->__listItemObjName.pNext = 0;  \
            head.firstItem->__listItemObjName.pPrevious = 0;  \
            head.firstItem = p; \
          } \
          POP_END: \
        }
/**
 * @brief  pop the last item in this list
 * @note  
 * @param {miniList_t} head : list head 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopTail(head, __listItemObjName) \
        (head.firstItem==0)?0:(head.firstItem->__listItemObjName.pPrevious);  \
        {   \
          if(head.firstItem != 0&&head.value != 0) \
          { \
            head.firstItem = head.firstItem->__listItemObjName.pPrevious; \
            head.value--; \
            if(head.value == 0){   \
              head.firstItem->__listItemObjName.pNext = 0;  \
              head.firstItem->__listItemObjName.pPrevious = 0;  \
              head.firstItem = 0; \
            }else{ \
              head.firstItem->__listItemObjName.pNext->__listItemObjName.pPrevious =  head.firstItem->__listItemObjName.pPrevious;  \
              head.firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = head.firstItem->__listItemObjName.pNext; \
              void* pNewFirst =  head.firstItem->__listItemObjName.pNext; \
              head.firstItem->__listItemObjName.pNext = 0;  \
              head.firstItem->__listItemObjName.pPrevious = 0;  \
              head.firstItem = pNewFirst; \
            } \
          }\
        }
        
void list_initList(list_t *list, uint32_t listMaxValue);
error_t list_insertList(list_t *list, listItem_t *item);
error_t list_insertHead(list_t *list, listItem_t *item);
error_t list_insertTail(list_t *list, listItem_t *item);
error_t list_removeformList(listItem_t *item);

#endif
