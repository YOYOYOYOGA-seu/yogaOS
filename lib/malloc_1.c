/*
 * @Author Shi Zhangkun
 * @Date 2020-09-12 02:25:04
 * @LastEditTime 2020-09-12 07:39:13
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/malloc_1.c
 */
#include "yogaOS/malloc.h"
#include "unistd.h"


/* extern -------------------------------------------------*/
extern void * mem_getHeapLocation(void);  // arch relevant

/**
 * @brief  Delet a block from using map
 * @note  
 * @param {memBlock_t *} ptrLast: Point to the last block of the
 *                                block wait to be delet. NULL if
 *                                it is the first block
 *        {uint32_t} index :
 * @retval error_t
 */
static error_t delFromUsingMap(memBlock_t *ptrLast,memArea_t *memArea)
{
  if(ptrLast != NULL)
  {
    if(ptrLast->pNext <= (memBlock_t *)memArea->pTop && ptrLast->pNext >= (memBlock_t *)memArea->pBase)
    {
      memArea->usingSize -= sizeof(memBlock_t) + ptrLast->pNext->size; 
      memArea->usingBlockNum--;
      ptrLast->pNext = ptrLast->pNext->pNext;
      return 0;
    }
  }
  else  // if ptrLast == NULL,then delet the first block
  {
    memArea->usingSize -= sizeof(memBlock_t) + memArea->pUsingMapBase->size; 
    memArea->usingBlockNum--;
    memArea->pUsingMapBase = memArea->pUsingMapBase->pNext;
    return 0;
  }
  return -1;
}

/**
 * @brief  Delet a block from ide map
 * @note  
 * @param {memBlock_t *} ptrLast: Point to the last block of the
 *                                block wait to be delet. NULL if
 *                                it is the first block
 *        {uint32_t} index :
 * @retval error_t
 */
static error_t delFromIdeMap(memBlock_t *ptrLast,memArea_t *memArea)
{
  if(ptrLast != NULL)
  {
    if(ptrLast->pNext <= (memBlock_t *)memArea->pTop && ptrLast->pNext >= (memBlock_t *)memArea->pBase)
    {
      /*the block size = ideBl_xxx.size + sizeof(memBlock_t),the ideBl_xxx.size was added to idleSize,
      but the sizeof(memBlock_t) was added to usingSize. So you should minus both of them */
      memArea->idleSize -= ptrLast->pNext->size; 
      memArea->usingSize -= sizeof(memBlock_t); 
      memArea->idleBlockNum --; 
      ptrLast->pNext = ptrLast->pNext->pNext;
      return 0;
    }
  }
  else
  {
    memArea->idleSize -= memArea->pIdleMapBase->size; 
    memArea->usingSize -= sizeof(memBlock_t); 
    memArea->idleBlockNum --; 
    memArea->pIdleMapBase = memArea->pIdleMapBase->pNext;
    return 0;
  }
  
  return -1;
}


/**
 * @brief  add a mem block to using Map
 * @note  Using map is ascending sorted by address size
 * @param {memBlock_t *} ptr: Point to the block wait to be added
 *        {uint32_t} index: index of the mem area
 * @retval always 0
 */
static error_t addToUsingMap(memBlock_t *ptr,memArea_t *memArea)
{
  uint32_t i;
  memBlock_t * pTemp = memArea->pUsingMapBase;

  memArea->usingBlockNum++;
  memArea->usingSize += ptr->size + sizeof(memBlock_t);
  /* Conditon witch the block should be add at the base of map */
  if(pTemp == NULL || ptr < pTemp)
  {
    memArea->pUsingMapBase = ptr;
    ptr->pNext = pTemp;
    return 0;
  }
  /* Travese map */
  for(i = 0; i < memArea->usingBlockNum; i++)
  {
    if(ptr < pTemp->pNext || pTemp->pNext == NULL)
      goto addToMap;
    pTemp = pTemp->pNext;
  }
  goto addToMap;

addToMap:
  ptr->pNext = pTemp->pNext;
  pTemp->pNext = ptr;
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
static memBlock_t *mergeIdeBlock(memBlock_t *ptr,memArea_t *memArea)
{
  
  /* Current ide block num, because after one merge operate, the
  memArea->idleBlockNum would minus once ,and that would cause 
  the travese circulation finish earlier than it should be*/
  uint32_t crtidleBlockNum = memArea->idleBlockNum; 
  int i;

  memBlock_t *pTemp = memArea->pIdleMapBase;
  memBlock_t *pLast = NULL;
  void *pNextSpace = (char *)ptr + sizeof(memBlock_t) + ptr->size;
  for(i = 0;(pTemp != NULL && i < crtidleBlockNum ); i++)
  {
    if(pTemp == pNextSpace)  //pTemp point to the next continuous block of ptr
    {
      delFromIdeMap(pLast,memArea);
      ptr->size += pTemp->size + sizeof(memBlock_t);
    }
    else if((memBlock_t *)((char *)pTemp + sizeof(memBlock_t) + pTemp->size) == ptr)
    {
      delFromIdeMap(pLast,memArea);
      pTemp->size += ptr->size + sizeof(memBlock_t);
      ptr = pTemp;
      
    }
    else   //When one block is delete, the next block's last block don't change
    {
      pLast = pTemp;
    }
    
    pTemp = pTemp -> pNext;
  }
  return ptr;   //Must return the new ptr to update the ptr in function addToIdeMap()
}
/**
 * @brief add a mem block to ide Map
 * @note  Using map is ascending sorted by block memory size
 * @param {memBlock_t *} ptr: Point to the block wait to be added
 *        {uint32_t} index: index of the mem area
 * @retval always 0
 */
static error_t addToIdeMap(memBlock_t *ptr,memArea_t *memArea)
{
  uint32_t i;
  memBlock_t * pTemp;
  /* merge the continued block, and update ptr (The ptr many chance after
  merge)*/
  ptr = mergeIdeBlock(ptr,memArea); 

  memArea->idleBlockNum++;
  memArea->idleSize += ptr->size ;
  memArea->usingSize += sizeof(memBlock_t); 

  pTemp = memArea->pIdleMapBase;
  /* Conditon witch the block should be add at the base of map */
  if(pTemp == NULL || ptr->size <= pTemp->size)
  {
    memArea->pIdleMapBase = ptr;
    ptr->pNext = pTemp;
    return 0;
  }
  /* Travese map */
  for(i = 0;i < memArea->idleBlockNum; i++)
  {
     /*The "if,else if" is to prevent when pTemp->pNext == NULL, access the NULL address */
    if(pTemp->pNext == NULL)
    {
      goto addToMap;
    }
    else if(ptr->size <= pTemp->pNext->size)  
    {
      goto addToMap;
    }
    pTemp = pTemp->pNext;
  }
  goto addToMap;

addToMap:
  ptr->pNext = pTemp->pNext;
  pTemp->pNext = ptr;
  return 0;
}



/**
 * @brief  To alloc a memory space
 * @note  
 * @param {size_t} size: Alloc size
 *        {uint32_t} index: Index of mem area
 * @retval point to the base of mem space
 */
void *malloc(size_t size)
{
  if(size == 0)
    return NULL;
  size = (size - size%AIGN_SIZE) + ((size%AIGN_SIZE)>0) * AIGN_SIZE;
  memArea_t *memArea = mem_getHeapLocation();
  memBlock_t *pTemp = memArea->pIdleMapBase;
  memBlock_t *pNew = NULL;  //before alloc complate pNew point to the last pTemp.
  uint32_t i;
  for(i = 0 ; (pTemp != NULL&&i < memArea->idleBlockNum); i++)
  {
    if(size + sizeof(memBlock_t) + AIGN_SIZE< pTemp->size)  //Condition to creat a new block
    {
      if(delFromIdeMap(pNew,memArea) != 0) // Internal error : can't delet ide block
        goto retNULL;
      pNew = (memBlock_t *)((char*)pTemp + (pTemp->size - size));
      pTemp->size -= size + sizeof(memBlock_t);
	    pNew->size = size;
      addToIdeMap(pTemp,memArea);
      addToUsingMap(pNew,memArea);
      goto retPtr;
    }
    else if(size <= pTemp->size)  //Condition to use current block
    {
      if(delFromIdeMap(pNew,memArea) != 0) // Internal error : can't delet ide block
        goto retNULL;
      pNew = pTemp;
      addToUsingMap(pNew,memArea);
      goto retPtr;
    }
    pNew = pTemp;          //before alloc complate pNew point to the last pTemp.
    pTemp = pTemp->pNext;
  }
  goto retNULL;    //No space can alloc
  
retPtr:      //retrun base point of the mem alloced space 
  return (void*)(pNew + 1);
retNULL: 
  return NULL;
}

/**
 * @brief free a mem space 
 * @note  
 * @param {void *} ptr: Point to the mem space wait to
 *                      be free
 * @retval error_t
 */
void free(void *ptr)
{
  uint32_t i,j;
  memBlock_t *pTemp = NULL;
  memBlock_t *pLast = NULL;
  memArea_t *memArea= mem_getHeapLocation();
  /* Find which area the ptr belong to */
  if(ptr <= memArea->pTop && ptr >= memArea->pBase)  
  {
    pTemp = memArea->pUsingMapBase;
    for(j = 0;(pTemp != NULL && j < memArea->usingBlockNum); j++ )
    {
      /* Find which block the ptr represent */
      if(ptr >=(void *)(pTemp + 1) && ptr < (void *)((char *)(pTemp + 1) + pTemp->size))
      {
        if(delFromUsingMap(pLast,memArea) != 0) // Internal error : can't delet ide block
          return ; 
        addToIdeMap(pTemp,memArea);
        ptr = NULL;
        return ;
      }
      pLast = pTemp;
      pTemp = pTemp->pNext;
    }
    return ;  //this ptr don't belong to any block that is uder using
  }
	return ;  //this ptr don't belong to any area be managed
}

