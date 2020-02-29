/*
 * @Author Shi Zhangkun
 * @Date 2020-02-21 20:25:27
 * @LastEditTime 2020-02-29 09:27:04
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/sched.h
 */
#ifndef __SCHED_H
#define __SCHED_H

#include "type.h"
#include "list.h"
#include "mm_page.h"
/* -------------------------------- define ---------------------------------- */
#define SCHED_MAX_PRIO_NUM            16

#define SCHED_SYS_STASK_PRIO_H        0
#define SCHED_SYS_STASK_PRIO_N        1

#define SCHED_MAX_TASK_NAME_SIZE      15
// PCB&ring0  L1 page tbl  L2 page tbl x2  stack
#define TASK_DEFUALT_TIME_SLICE       15   //unit :system tick
#define TASK_INIT_NEED_PAGE_NUM       5   

#define TASK_READY_LIST_MAX_VALUE     0xFFFFFFFF
#define TASK_HUNG_UP_LIST_MAX_VALUE     0xFFFFFFFF

/* ---------------------------- type define -------------------------------- */
typedef struct{
  volatile uint32_t state;
  //point to the physical stack base page in linear address space
  // don't represent the current top of stack(this well be direct recording by register)
  void *pStack;
  pid_t  pid;    //prio 0 respect system task (for test when don't have fork() function)
  pid_t  pidStatic;
  uint32_t totalTimeSlice;  
  uint32_t timeLeft; // time left in this round (Time slice scheduling)
  char name[SCHED_MAX_TASK_NAME_SIZE + 1];
  uint32_t prio;
  void *pArchRelvant;
  void *L1PageTbl;
  listItem_t  stateListItem;
  listItem_t  eventListItem;
  pageList_t  usingPageList;  //task using page memory manage list

}PCB_t;

typedef enum{
  TASK_READY = 0,
  TASK_RUN,
  TASK_CHOKE,
  TASK_PENDING,
  TASK_STOP
}taskState_t;

typedef enum{
  SCHEDULER_RUN = 0,
  SCHEDULER_PENDING,
  SCHEDULER_STOP
}shcedulerState_t;
extern PCB_t * currentActiveTask;
/* ------- Arch relevant function (defined in arch/xxx/xxx/xxx.c) ----------------- */
error_t sched_initPCBArchRelevant(PCB_t *pPCB, void (*taskFunc)(void));
error_t sched_initTaskPage(PCB_t * pPCB);
void sched_loadFirstTask(PCB_t *pPCB);
//void sched_switchToTask(PCB_t *pPCB);
/* ----------------------- function declaration ------------------------------------ */
error_t sched_creatNewSysTask(void (*taskFunc)(void), uint32_t codeSize, uint32_t prio, const char* name);
error_t sched_initPCB(PCB_t *pPCB,uint32_t prio, const char* name,void (*taskFunc)(void),pageList_t temp);
pid_t sched_registerPID(void);
error_t sched_initScheduler(void);
error_t sched_addToList(PCB_t *pPCB, taskState_t state);

void sched_startScheduler(void);
void sched_timeTick(void);
uint32_t sched(void);
#endif