/*
 * @Author Shi Zhangkun
 * @Date 2020-02-18 21:06:24
 * @LastEditTime 2020-02-28 02:15:57
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/system_x86.h
 */
#ifndef __SYSTEM_X86_H
#define __SYSTEM_X86_H

#include "address.h"
#include "yogaOS/types.h"
typedef struct{
  uint32_t memSize;

  uint32_t idleMemSize;
  uint32_t phyPageNum;
  uint32_t idlePageNum;
  
}sysMsg_t;


extern const sysMsg_t * const sysMessage;
#endif
