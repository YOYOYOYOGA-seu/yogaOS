/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 05:14:13
 * @LastEditTime 2020-08-08 07:26:53
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/page.h
 */
#ifndef __PAGE_H
#define __PAGE_H
#include "yogaOS/types.h"
#include "yogaOS/list.h"
#include "errno.h"
#include "mm.h"
/* ---------------------------------- define ------------------------------------ */

//temporary Invalid page table item pointer, Some time's when alloc a physical page, the
// page table maybe not ready(such as alloc a page for page table), but the page_t.pOwner
// also represent if this physical page have been using, so we use 0xffffffff to sign this 
// physical page have been occupied, but haven't have a page table item point to it.
// After the page table ready, it must be changed using function phyPageSetOwner()
#define PHY_PAGE_ALLOC_NO_OWNER      0xffffffff  

typedef miniList_t(page_t) pageList_t;
/* ------- Arch relevant function (defined in arch/xxx/xxx/xxx.c) ----------------- */

page_t *page_locateList(uint32_t *size, uint32_t *phyrBase, uint32_t * linearBase); //old vision use,now abandon

/* ------------------------------function define ----------------------------- */
#define page_allocOne(pUsingList,index)  page_allocByOrder(pUsingList,index,0)
/* ------------------------------function declaration ----------------------------- */
void *page_allocByOrder(pageList_t *usingList, zoneIndex_t index, int order);
error_t page_checkIdleMemNum(uint32_t allocNum,zoneIndex_t index);
void page_initPageDesc(zoneIndex_t index);


#endif