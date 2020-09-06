/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 21:59:06
 * @LastEditTime 2020-09-06 00:12:42
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/page_x86.h
 */
#ifndef __PAGE_X86_H
#define __PAGE_X86_H

#include "address.h"
#include "yogaOS/types.h"
#include "errno.h"

typedef uint32_t pageTblItem_t;
/* ------------------------ define --------------------------- */
/**
 * @brief  Transfer address in high mapping area to phy addr
 * @note  
 * @param {type} none
 * @retval none
 */
#define pToPhy(a)    ((uint32_t)(a) - SYS_BASE_LINEAR_ADDR)  
/**
 * @brief  Transfer phy addr to it's linear addr in high mapping area
 * @note  
 * @param {type} none
 * @retval none
 */
#define phyToLin(a)   ((uint32_t)(a) + SYS_BASE_LINEAR_ADDR) 
/* ------------------ PTE and PDE setting -------------------- */
#define PDE_P    0x01
#define PDE_RW   0x02
#define PDE_US   0x04
#define PDE_PWT  0x08
#define PDE_PCD  0x10
#define PDE_A    0x20
#define PDE_PAT  0x80
#define PDE_G    0x100

#define PTE_P    0x01
#define PTE_RW   0x02
#define PTE_US   0x04
#define PTE_PWT  0x08
#define PTE_PCD  0x10
#define PTE_A    0x20
#define PTE_D    0x40
#define PTE_PS   0x80
#define PTE_G    0x100


#endif