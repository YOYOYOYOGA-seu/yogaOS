/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 05:14:13
 * @LastEditTime 2020-02-26 05:14:18
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/mm_page.h
 */

#include "type.h"
#include "list.h"
#include "errno.h"

/* ------------------------------- type define ------------------------------------- */
typedef miniListItem_t page_t;  //page manage list item, storing the page base phy addr, owner ...

typedef miniList_t     pageList_t; //page manage list

/* ---------------------------------- define ------------------------------------ */

//temporary Invalid page table item pointer, Some time's when alloc a physical page, the
// page table maybe not ready(such as alloc a page for page table), but the page_t.pOwner
// also represent if this physical page have been using, so we use 0xffffffff to sign this 
// physical page have been occupied, but haven't have a page table item point to it.
// After the page table ready, it must be changed using function phyPageSetOwner()
#define PHY_PAGE_ALLOC_NO_OWNER      0xffffffff  

/* ------- Arch relevant function (defined in arch/xxx/xxx/xxx.c) ----------------- */

page_t *mm_locatePageList(uint32_t *size, uint32_t *phyrBase, uint32_t * linearBase);


/* ------------------------------function declaration ----------------------------- */
void *mm_allocOnePage(pageList_t *usingList);
error_t mm_checkIdleMemNum(uint32_t allocNum);
void mm_initPageManage(void);