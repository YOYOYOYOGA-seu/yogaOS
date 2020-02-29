#include "type.h"
#include "init.h"
#include "sched.h"


extern void initInterrupt(void);
int a = 1;
int b = 1;
char d = 'a';
char *c = &d;

void init_task(void)
{
  int a = 1;
  while(1)
  {

  }
}


void testTask2(void) //test scheduler
{
  int a = 2;
  while(1)
  {

  }
}

int main(void){
  initInterrupt();
  initSysMsg();
  initMemManage();
  sched_initScheduler();
  sched_creatNewSysTask(init_task,512,0,"init_task\0");
  sched_creatNewSysTask(testTask2,512,0,"testTask2\0");
  sched_startScheduler();
  while(1)
  {

  }
  return 0;
}

