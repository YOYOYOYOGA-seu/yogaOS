/*
 * @Author Shi Zhangkun
 * @Date 2020-02-18 02:53:47
 * @LastEditTime 2020-02-29 07:20:33
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/start.h
 */
#ifndef __START_H
#define __START_H

#define selGlobalData     SEL_GDT_GLOBAL_DATA
#define selPageDir        SEL_GDT_PAGE_DIR
#define selPageTbl        SEL_GDT_PAGE_TBL
#define selVideo          SEL_GDT_VIDEO

#define sysMemSize        PHY_SYS_MESSAGE_ADDR

#define NUM_OF_TMP_MAP_IN_PAGE_DIR     4    //temporary mapping in L1 page table low addr area for system init 

#define DA_386I_GATE 0x8E + 0x60
#endif