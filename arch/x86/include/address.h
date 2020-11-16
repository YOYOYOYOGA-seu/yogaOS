/*
 * @Author Shi Zhangkun
 * @Date 2020-02-15 22:02:03
 * @LastEditTime 2020-11-15 11:07:29
 * @LastEditors Shi Zhangkun
 * @Description 
 * 
 * ///////////////////////  physical address distribution  //////////////////////////
 *    |                         |
 *    |  idle mem area (task)   |
 *    |_________________________| 0x00c0 0000
 *    |                         |
 *    |     disk R/W buffer     |
 *    |_________________________| 0x0060 0000
 *    |                         |
 *    |    page manage list     |
 *    |_________________________| 0x0020 0000
 *    |    System page table    |
 *    |_________________________| 0x0010 1000
 *    |  System page dir(init)  |
 *    |_________________________| 0x0010 0000
 *    |                         |
 *    |   BIOS,graphics RAM...  |
 *    |_________________________| 0x0009 FC00
 *    |          Loader         |
 *    |_________________________| 0x0009 1800
 *    |           IDT           |
 *    |_________________________| 0x0009 1000
 *    |           GDT           |
 *    |_________________________| 0x0009 0800
 *    |      system message     |
 *    |_________________________| 0x0009 0000
 *    |                         |
 *    |       system code       |                           // .bss start = 0x00070000;
 *    |                         |
 *    |_________________________| 0x0000 1000
 *    |   system stack (init)   |    
 *    | global variable(runing) |
 *    |_________________________| 0x0000 0000
 * 
 * 
 * * ///////////////////////  linear address distribution  //////////////////////////
 * 
 *    |       haven't use       |
 *    |_________________________| 0x8000 0000
 *    |                         |    
 *    |  idle physical memory   |            //linear map of all idle mem, max size = 1GB(idle mem area + sys reserve area)
 *    |                         |            
 *    |_________________________| 0x40c0 0000 ------------- physical memory map -------------
 *    |                         |
 *    |     disk R/W buffer     |              //save the FS index on the disk
 *    |_________________________| 0x4060 0000
 *    |                         |
 *    |    page manage list     |
 *    |_________________________| 0x4020 0000
 *    |     system page table   |               //L2 table describe the system address higher than 1G
 *    |_________________________| 0x4010 1000
 *    |      init page dir      |
 *    |_________________________| 0x4010 0000
 *    |                         |
 *    |   BIOS,graphics RAM...  |
 *    |_________________________| 0x4009 FC00
 *    |          Loader         |
 *    |_________________________| 0x4009 1800
 *    |           IDT           |
 *    |_________________________| 0x4009 1000
 *    |           GDT           |
 *    |_________________________| 0x4009 0800
 *    |      system message     |
 *    |_________________________| 0x4009 0000
 *    |                         |
 *    |       system code       |             // .bss start = 0x00070000;
 *    |                         |
 *    |_________________________| 0x4000 1000
 *    |  global variable area   |    
 *    |_________________________| 0x4000 0000 ---------- system reserve area --------------
 *    |       haven't use       |
 *    |_________________________| 0x3FE0 0000
 *    |                         |             //L2 describe the low 1G linear address,Now haven't use
 *    |  task page tbl (code)   |             //because page table describle page table memory is too complex
 *    |_________________________| 0x3FD0 0000
 *    |       haven't use       |
 *    |_________________________| 0x3FC0 2000
 *    |      task page dir      |             //L1 page (the L2 table of task not mapped in linear addr space)
 *    |_________________________| 0x3FC0 1000
 *    |   PCB & ring 0 stack    |
 *    |_________________________| 0x3FC0 0000 ---------------- task data -----------------
 *    |        task heap        |             //user task can apply almost 500MB mem at most
 *    |_________________________| 0x2040 0000
 *    |                         |
 *    |                         |
 *    |     task code, data     |             //user code, data area,(.bss,.data,.text) size: 512MB
 *    |                         |
 *    |_________________________| 0x0040 0000
 *    |        task stack       |             // stack growing down
 *    |_________________________| 0x0000 2000
 *    |        return code      |             //user main func return handler
 *    |_________________________| 0x0000 1000
 *    |        don't use        |             //don't alloc phy memory, for intercept null pointer 
 *    |_________________________| 0x0000 0000 ---------------------------------------------
 * 
 * ///////////////////////////////////////////////////////////////////////
 * 
 *              @@@ Note : Use Linear Address and  Physical Address @@@
 * 
 *   Physical address only used in two condition :
 *    1. Initlize system, before the page table init complete(before jump to C )
 *    2. Opreate page about strcuts, regisiters, such as PDE, PTE and cr3(save page dir phy base addr)
 * 
 *   And in all C files, the physical address will be declared as uint32_t, in those files:
 *    1. page_x86.h, the page manage list item (prototype is sigListItem_t_t in yogaOS/list.h),the
 *       item.value saves the base physical address of the phy page which be maanged.
 *    ....
 *   Linear address usually be used as pointers, because it is convenient for read or write.
 *   You can only R/W memory by using linear address to those physical memories have been mapped in linear address space.
 * 
 *   If you want write some strcuts or registers saves phy addr, such as PTE, PDE or cr3, you can use
 *   pToPhy() to transform the pionter to physical address.(defined in page_x86.h)
 *   
 * @FilePath /project/arch/x86/include/address.h
 */
#ifndef __ADRESS_H
#define __ADRESS_H

/* ---------------------------System segment selector --------------------------- */

#define SEL_GDT_GLOBAL_DATA    0x008
#define SEL_GDT_GLOBAL_CODE    0x010
#define SEL_GDT_PAGE_DIR       0x018
#define SEL_GDT_PAGE_TBL       0x020
#define SEL_GDT_VIDEO          0x028
#define SEL_GDT_LDT            0x030


/* ------------------ physical address map ------------- */

#define PHY_SYS_STACK_TOP_ADDR        0x00000
#define PHY_SYS_CODE_BASE_ADDR        0x01000
#define PHY_SYS_BSS_BASE_ADDR         0x70000
#define PHY_LOADER_BASE_ADDR          0x90000
#define PHY_VIDEO_MEM_BASE_ADDR       0xb8000
#define PHY_SYS_MESSAGE_ADDR          PHY_LOADER_BASE_ADDR
#define PHY_GDT_BASE_ADDR             (PHY_LOADER_BASE_ADDR + 0x0800)
#define PHY_IDT_BASE_ADDR             (PHY_GDT_BASE_ADDR + 0x0800)
#define PHY_LOADER_CODE_BASE_ADDR     (PHY_IDT_BASE_ADDR + 0x0800)

#define PHY_SYS_PAGE_DIR_BASE_ADDR    0x100000
#define PHY_SYS_PAGE_TBL_BASE_ADDR    0x101000
#define PHY_PAGE_MM_LIST_BASE_ADDR    0x200000
#define PHY_FILE_BUFF_BASE_ADDR       0x600000
#define PHY_IDLE_MEM_BASE_ADDR        0xc00000
/* ------------------ segment and area size (physical address) --------------- */
#define LOADER_CODE_OFFSET_SIZE   (PHY_LOADER_CODE_BASE_ADDR - PHY_LOADER_BASE_ADDR)

#define SYS_STACK_SIZE            (PHY_SYS_CODE_BASE_ADDR - PHY_SYS_STACK_TOP_ADDR)
#define SYS_BSS_SIZE              (PHY_LOADER_BASE_ADDR - PHY_SYS_BSS_BASE_ADDR)
#define GDT_AREA_SIZE             (PHY_IDT_BASE_ADDR - PHY_GDT_BASE_ADDR)
#define IDT_AREA_SIZE             (PHY_LOADER_CODE_BASE_ADDR - PHY_IDT_BASE_ADDR)
#define SYSTEM_RESERVE_AREA_SIZE  (PHY_IDLE_MEM_BASE_ADDR )       
 
#define SYS_PAGE_DIR_SIZE         (PHY_SYS_PAGE_TBL_BASE_ADDR - PHY_SYS_PAGE_DIR_BASE_ADDR)
#define SYS_PAGE_TBL_SIZE         (PHY_PAGE_MM_LIST_BASE_ADDR  - PHY_SYS_PAGE_TBL_BASE_ADDR)

#define PAGE_MM_LIST_SIZE         (PHY_FILE_BUFF_BASE_ADDR - PHY_PAGE_MM_LIST_BASE_ADDR)
#define SYS_FILE_BUFF_SIZE        (PHY_IDLE_MEM_BASE_ADDR - PHY_FILE_BUFF_BASE_ADDR)
#define VIDEO_MEM_SIZE            0xffff

#define SYS_MSG_MEM_SIZE_ADDR     PHY_SYS_MESSAGE_ADDR         


/* -------------------------- mssege and area size -------------------------- */
#define PAGE_SIZE                 0x1000   // 4K


#define PTE_SIZE                  0x0004

#define MAX_SUPPRT_MEM_SIZE       ((SYS_PAGE_TBL_SIZE)/4)*PAGE_SIZE
#define MIN_SUPPRT_MEM_SIZE       2*(PHY_IDLE_MEM_BASE_ADDR)


/* -------------------------- Linear address map ------------------------- */  
#define TASK_RETURN_HANDLER_ADDR        0x00001000        
#define TASK_STACK_TOP                  0x00002000
#define TASK_STACK_BASE                 0x00400000   // stack growing down
#define TASK_CODE_START_ADDR            0x00400000   
#define TASK_HEAP_START_ADDR            0x20400000
#define PCB_BASE_ADDR                   0x3fc00000
#define TASK_RING_0_STACK_TOP           0x3fc00400
#define TASK_RING_0_STACK_BASE          0x3fc01000           
#define TASK_PAGE_DIR_BASE_ADDR         0x3fc02000

#define TASK_PAGE_TBL_BASE_ADDR         0x3fd00000

#define SYS_BASE_LINEAR_ADDR         0x40000000     //1G
#define SYSTEM_STACK_ADDR               (SYS_BASE_LINEAR_ADDR + PHY_SYS_STACK_TOP_ADDR)
#define SYSTEM_CODE_BASE_ADDR           (SYS_BASE_LINEAR_ADDR + PHY_SYS_CODE_BASE_ADDR)
#define SYSTEM_BSS_BASE_ADDR           (SYS_BASE_LINEAR_ADDR + PHY_SYS_BSS_BASE_ADDR)
#define LOADER_BASE_ADDR                (SYS_BASE_LINEAR_ADDR + PHY_LOADER_BASE_ADDR)
#define VIDEO_MEM_BASE_ADDR             (SYS_BASE_LINEAR_ADDR + PHY_VIDEO_MEM_BASE_ADDR)
#define SYS_MESSAGE_ADDR                (SYS_BASE_LINEAR_ADDR + PHY_SYS_MESSAGE_ADDR)
#define GDT_BASE_ADDR                   (SYS_BASE_LINEAR_ADDR + PHY_GDT_BASE_ADDR)
#define IDT_BASE_ADDR                   (SYS_BASE_LINEAR_ADDR + PHY_IDT_BASE_ADDR)
#define LOADER_CODE_BASE_ADDR           (SYS_BASE_LINEAR_ADDR + PHY_LOADER_CODE_BASE_ADDR)

#define SYS_PAGE_DIR_BASE_ADDR          (SYS_BASE_LINEAR_ADDR + PHY_SYS_PAGE_DIR_BASE_ADDR)
#define SYS_PAGE_TBL_BASE_ADDR          (SYS_BASE_LINEAR_ADDR + PHY_SYS_PAGE_TBL_BASE_ADDR)
#define PAGE_MM_LIST_BASE_ADDR          (SYS_BASE_LINEAR_ADDR + PHY_PAGE_MM_LIST_BASE_ADDR)
#define FILE_BUFF_BASE_ADDR             (SYS_BASE_LINEAR_ADDR + PHY_FILE_BUFF_BASE_ADDR)
#define IDLE_MEM_BASE_ADDR              (SYS_BASE_LINEAR_ADDR + PHY_IDLE_MEM_BASE_ADDR)
#define RESERVE_AREA_ADDR               0x80000000
/* -------------------------- Linear address area size ------------------------- */
#define TASK_STACK_SIZE                 SYS_STACK_SIZE
#define TASK_RING_0_STACK_SIZE          (TASK_RING_0_STACK_BASE - TASK_RING_0_STACK_TOP)
#define SUPT_MAX_PHY_MEM_SIZE           (RESERVE_AREA_ADDR - SYS_BASE_LINEAR_ADDR)    

#endif
