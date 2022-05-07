/*
 * @Author Shi Zhangkun
 * @Date 2020-07-15 19:22:17
 * @LastEditTime 2022-05-07 14:57:52
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/mm.h
 */ 
#ifndef __MM_H
#define __MM_H
#include "yogaOS/list.h"
#include "yogaOS/types.h"

/* max order of buddy system, the max bock size = 2^n pages; The quantity of order is BUDDY_MAX_ORDER + 1  */
#define BUDDY_MAX_ORDER    11 

#define PAGE_FLAG_SLOB_MASK   0x01

typedef struct page{
  miniListItem_t(struct page) lru;
  uint32_t flag:8;
  uint32_t index:24;   /* page desc index in the vector, can used to caculate the page's offset to the base addr (multiply by PAGE_SIZE) */
  uint8_t bOrder;  /* buddy order of this page desc */
  const uint8_t fatherZone; 
  uint16_t __left_16;  /* align 32 , for future use */
}page_t;

#define SYSTEM_ZONE_NUM 2

typedef enum{
  HS_CACHE = 0,
  IDLE_AREA
}zoneIndex_t;

/** zone_t defined a area of phy memory that be managed */ 
typedef struct zone{
  /** the point to the page desc array, if NULL after init represent the 
   * space of page desc array need bootstrap
   */
  page_t * pPageDescArray;
  
  int  maxFreeOrder;  /* max size free block's order in this zone's buddy system */
  miniList_t(page_t) freeBlock[BUDDY_MAX_ORDER + 1];
  /** flag represent the mem zone manage way: 
   * DYNAMIC:  managed dynamically, the linear addr of the pages be alloced are not 
   * ascertain, for example the idle area in arch x86
   * STATIC: The zone are statically mapped in linear addr space, and never change,for 
   * example the disk R/W buff in arch x86
   */
  enum {
    INVILD = 0,   
    DYNAMIC,
    STATIC     /* don't use to alloc dynamically */
  }flag;
  
  uint32_t totalPages; /* total pages of this zone*/
  uint32_t managedPages; /* total pages of this zone that be managed, for flag = DYNAMIC, this equal to totalPages*/
  uint32_t freePages;
  uint32_t phyBase;     /* mem zone start addr */
  /* the linear mapping area base addr of this phy mem, if don't have set as NULL */
  
  uint32_t linearBase;  
}zone_t;

/* ------- Arch relevant function (defined in arch/xxx/xxx/xxx.c) ----------------- */

void zone_sysZoneInit(void);
/* ------------------------------function declaration ----------------------------- */
void zone_init(void);
void heap_initMalloc(void* firstPage, void* heapBase);

#endif