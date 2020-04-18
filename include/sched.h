/*
 * @Author Shi Zhangkun
 * @Date 2020-02-21 20:25:27
 * @LastEditTime 2020-04-18 06:36:43
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/sched.h
 */
#ifndef __SCHED_H
#define __SCHED_H

#include "type.h"
#include "list.h"
#include "page.h"
/* -------------------------------- define ---------------------------------- */
#define SCHED_MAX_TASK_NUM              1024  //max task number system support 

#define SCHED_MAX_P_PRIO_NUM            16
#define SCHED_MAX_T_PRIO_NUM            19 //max t_prio
#define SCHED_SYS_TASK_P_PRIO_H        0
#define SCHED_SYS_TASK_P_PRIO_N        1

#define SCHED_MAX_TASK_NAME_SIZE      15
       

// PCB&ring0  L1 page tbl  L2 page tbl x2  stack
#define TASK_DEFUALT_T_PRIO           10
#define TASK_DEFUALT_P_PRIO           15

#define TASK_MAX_TIME_SLICE           20   //unit :system tick
#define TASK_INIT_NEED_PAGE_NUM       6   

#define TASK_READY_LIST_MAX_VALUE     0xFFFFFFFF
#define TASK_SUSP_LIST_MAX_VALUE     0xFFFFFFFF

/* ---------------------------- type define -------------------------------- */
typedef struct{
  volatile uint32_t status;
  //point to the physical stack base page in linear address space
  // don't represent the current top of stack(this well be direct recording by register)
  void *pStackPage;
  void *retFuncPage;  //point to the page base addr which save the handle of task return(exit)
  pid_t  pid;    
  pid_t  pidStatic;
  uint32_t totalTimeSlice;  
  uint32_t timeLeft; // time left in this round (Time slice scheduling)
  char name[SCHED_MAX_TASK_NAME_SIZE + 1];
  uint32_t p_prio; //preempting priority,p_prio 0,1 respect system task (for test when don't have fork() function)
  uint32_t t_prio; //time slice prio, 0 respect highest, have max time slice size.time slice = (TASK_MAX_TIME_SLICE - p_rio)* 10ms

  int tty;         // tty this task belong to
  void *pArchRelvant;
  void *L1PageTbl;
  listItem_t  stateListItem;
  listItem_t  eventListItem;
  pageList_t  usingPageList;  //task using page memory manage list

}PCB_t;

typedef enum{
  TASK_RUN = 0,
  TASK_READY,
  TASK_CHOKE,
  TASK_SUSPENDING,
  TASK_STOP
}taskState_t;

typedef enum{
  SCHEDULER_RUN = 0,
  SCHEDULER_PENDING,
  SCHEDULER_STOP
}shcedulerState_t;
extern PCB_t * currentActiveTask;
/* ------- Arch relevant function (defined in arch/xxx/xxx/xxx.c) ----------------- */
error_t task_initPCBArchRelevant(PCB_t *pPCB, void (*taskFunc)(void));
error_t task_initTaskPage(PCB_t * pPCB);
void sched_loadFirstTask(PCB_t *pPCB);
//void sched_switchToTask(PCB_t *pPCB);
/* ----------------------- function declaration ------------------------------------ */
error_t task_creatNewSysTask(void (*taskFunc)(void), uint32_t codeSize, uint32_t p_prio,uint32_t t_prio, const char* name);
error_t task_initPCB(PCB_t *pPCB,uint32_t p_prio,uint32_t t_prio, const char* name,void (*taskFunc)(void),pageList_t temp);
pid_t sched_registerPID(PCB_t * pPCB);
pid_t sched_getCurrentPID(void);
error_t sched_initScheduler(void);
error_t sched_addToList(PCB_t *pPCB);
error_t removeFromStateList(PCB_t *pPCB);
error_t sched_suspendTask(PCB_t *pPCB, uint32_t time);
error_t sched_wakeTask(void);
void sched_startScheduler(void);
void sched_timeTick(void);
uint32_t schedule(void);
#endif