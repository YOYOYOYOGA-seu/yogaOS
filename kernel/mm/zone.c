/*
 * @Author Shi Zhangkun
 * @Date 2020-07-15 23:06:47
 * @LastEditTime 2020-11-22 18:55:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/mm/zone.c
 */ 
#include "mm.h"
#include "yogaOS/list.h"
#include "yogaOS/types.h"
#include "errno.h"
#include "page.h"

zone_t sysMemZone[SYSTEM_ZONE_NUM];


void zone_init(void)
{
  for(int i=0; i<SYSTEM_ZONE_NUM; i ++)
  {
    for(int j=0; j<=SYSTEM_ZONE_NUM; j ++)
      miniList_init(&sysMemZone[i].freeBlock[j]);
  }
  zone_sysZoneInit();
  page_initPageDesc(IDLE_AREA);
  page_initPageDesc(HS_CACHE);
}