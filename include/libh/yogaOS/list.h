/*
 * @Author Shi Zhangkun
 * @Date 2020-02-21 20:59:03
 * @LastEditTime 2022-04-18 12:50:48
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/yogaOS/list.h
 */
#ifndef __LIST_H
#define __LIST_H

#include "yogaOS/types.h"

/* ------------------------ type define --------------------------- */
/* double linked  list */
struct list;
struct listItem;
typedef struct list list_t;
typedef struct listItem listItem_t;

struct listItem{
  unsigned int value;
  listItem_t * pNext;
  listItem_t * pPrevious;
  void* pOwner;
  list_t * pListHead;
};

struct list {
  unsigned int size;
  unsigned int listValueLimit;
  listItem_t *pFirstItem;
}; 

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
 * @param {miniList_t *} pHead : : list pHead
 * @retval none
 */
#define miniList_init(pHead){ \
          (pHead)->firstItem = 0; \
          (pHead)->value = 0; \
        }
/**
 * @brief  
 * @note  
 * @param {miniList_t *} pHead : : list pHead
 * @retval number of items in this list 
 */
#define miniList_size(pHead) (pHead)->value;

/**
 * @brief  templete func of match a item in list
 * @note  
 * @param 
 * @retval 
 */
#define __miniList_matchTemplate(pHead,pItem,__expl,__operator,__expr,__listItemObjName) {  \
  if((pHead)->firstItem != 0&&(pHead)->value > 0){ \
    void *pTempHead = (pHead)->firstItem; \
    while(!(__expl __operator __expr)) \
    { \
      (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pNext; \
      if((pHead)->firstItem == pTempHead) \
      { \
        (pHead)->firstItem = 0; \
        break; \
      } \
    } \
    pItem = (pHead)->firstItem; \
    (pHead)->firstItem = pTempHead; \
  }else{ \
    pItem = 0; \
  } \
}
/**
 * @brief match a item in list, search condition is the relationship between item member and a value
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __expl :  expression left, must be the member of list item 
 * @param {} __operator : operator, like == , < , >
 * @param {} __expr : expression left, must be a value 
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchMtoV(pHead,pItem,__expl,__operator,__expr,__listItemObjName) \
          __miniList_matchTemplate(pHead,pItem,(pHead)->firstItem->__expl,__operator,__expr,__listItemObjName)
/**
 * @brief match a item in list, search condition is the relationship between item member and item member
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} __expl :  expression left, must be the member of list item 
 * @param {} __operator : operator, like == , < , >
 * @param {} __expr : expression left, must be the member of list item
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchMtoM(pHead,pItem,__expl,__operator,__expr,__listItemObjName) \
          __miniList_matchTemplate(pHead,pItem,(pHead)->firstItem->__expl,__operator,(pHead)->firstItem->__expr,__listItemObjName)
 
/**
 * @brief match a item in list by function
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pItem : return the match result in this point 
 * @param {} equalFunc : compare function
 * @param {} Member : member of the item struct
 * @param {} target : match target
 * @param {} __listItemObjName : the name of the miniListItem object 
 * @retval 
 */
#define miniList_matchByFunc(pHead,pItem, equalFunc, Member, target,__listItemObjName) {  \
  if((pHead)->firstItem != 0&&(pHead)->value > 0){ \
    void *pTempHead = (pHead)->firstItem; \
    while(!equalFunc((pHead)->firstItem->Member, target)) \
    { \
      (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pNext; \
      if((pHead)->firstItem == pTempHead) \
      { \
        (pHead)->firstItem = 0; \
        break; \
      } \
    } \
    pItem = (pHead)->firstItem; \
    (pHead)->firstItem = pTempHead; \
  }else{ \
    pItem = 0; \
  } \
}

/**
 * @brief  insert a item to a mini list
 * @note  don't support circle, it mean's the firstItem.pPrevious and lastItem.pNext are both 0
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertHead(pHead,pItem,__listItemObjName) {   \
          if((pHead)->firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = (pHead)->firstItem;  \
            (pItem)->__listItemObjName.pPrevious = (pHead)->firstItem->__listItemObjName.pPrevious; \
            (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            (pHead)->firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
          } \
          (pHead)->firstItem = pItem; \
          (pHead)->value++;   \
        }
/**
 * @brief  insert a item to a mini list
 * @note  don't support circle, it mean's the firstItem.pPrevious and lastItem.pNext are both 0
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type>} pItem : point to the item waitting to insert
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_insertTail(pHead,pItem,__listItemObjName) {   \
          if((pHead)->firstItem != 0){   \
            (pItem)->__listItemObjName.pNext = (pHead)->firstItem;  \
            (pItem)->__listItemObjName.pPrevious = (pHead)->firstItem->__listItemObjName.pPrevious; \
            (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pItem);  \
            (pHead)->firstItem->__listItemObjName.pPrevious = (pItem);  \
          }else{ \
            (pItem)->__listItemObjName.pNext = (pItem);  \
            (pItem)->__listItemObjName.pPrevious = (pItem); \
             (pHead)->firstItem = pItem; \
          } \
          (pHead)->value++;   \
        }
/**
 * @brief  pop the first item in this list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopHead(pHead, __listItemObjName) (pHead)->firstItem;  \
        {   \
          if((pHead)->firstItem != 0&&(pHead)->value != 0) \
          { \
            (pHead)->value--; \
            if((pHead)->value == 0){   \
              (pHead)->firstItem->__listItemObjName.pNext = 0;  \
              (pHead)->firstItem->__listItemObjName.pPrevious = 0;  \
              (pHead)->firstItem = 0; \
            }else{ \
              (pHead)->firstItem->__listItemObjName.pNext->__listItemObjName.pPrevious =  (pHead)->firstItem->__listItemObjName.pPrevious;  \
              (pHead)->firstItem->__listItemObjName.pPrevious->__listItemObjName.pNext = (pHead)->firstItem->__listItemObjName.pNext; \
              void* p =  (pHead)->firstItem->__listItemObjName.pNext; \
              (pHead)->firstItem->__listItemObjName.pNext = 0;  \
              (pHead)->firstItem->__listItemObjName.pPrevious = 0;  \
              (pHead)->firstItem = p; \
            } \
          } \
        }
/**
 * @brief  pop the last item in this list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval <type> * : the point to the item be poped
 */
#define miniList_PopTail(pHead, __listItemObjName) \
        ((pHead)->firstItem==0)?0:((pHead)->firstItem->__listItemObjName.pPrevious);  \
        {   \
          if((pHead)->firstItem != 0) \
          { \
            (pHead)->firstItem = (pHead)->firstItem->__listItemObjName.pPrevious; \
            miniList_PopHead(pHead,__listItemObjName) \
          } \
        }
        
/**
 * @brief  remove item from a list
 * @note  
 * @param {miniList_t *} pHead : list pHead 
 * @param {<type*>} pHead : pItem
 * @param {} __listItemObjName : the name of the miniListItem object
 * @retval none
 */
#define miniList_remove(pHead,pItem,__listItemObjName)  \
        { \
          if((pHead)->firstItem != 0&&(pHead)->value != 0) \
          { \
            if((pHead)->firstItem == pItem){ \
              miniList_PopHead(pHead,__listItemObjName); \
            }else{ \
              pItem->__listItemObjName.pNext->__listItemObjName.pPrevious = pItem->__listItemObjName.pPrevious; \
              pItem->__listItemObjName.pPrevious->__listItemObjName.pNext = pItem->__listItemObjName.pNext; \
              pItem->__listItemObjName.pPrevious = 0; \
              pItem->__listItemObjName.pNext = 0; \
              (pHead)->value--; \
            } \
          } \
        }

void list_initList(list_t *list, uint32_t listMaxValue);
error_t list_insertList(list_t *list, listItem_t *item);
error_t list_insertHead(list_t *list, listItem_t *item);
error_t list_insertTail(list_t *list, listItem_t *item);
error_t list_removeformList(listItem_t *item);

#endif
