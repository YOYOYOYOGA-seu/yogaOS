#include "type.h"
#include "init.h"
#include "sched.h"
#include "unistd.h"
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
void idle_task(void) //test scheduler
{
  int a = 2;
  
  while(1)
  {
  }
}

void testTask2(void) //test scheduler
{
  int a = 2;
  int time = 0;
  
  while(1)
  {
    time++;
    sleep(5);
  }
}

void testTask3(void) //test scheduler
{
  int a = 2;
  int time = 0;
  pid_t pid;
  while(1)
  {
    time++;
    sleep(2);
    pid = getpid();
  }
}


int main(void){
  init8254Timer();
  initInterrupt();
  initSysMsg();
  initMemManage();
  sched_initScheduler();
  task_creatNewSysTask(init_task,512,1,"init_task\0");
  task_creatNewSysTask(idle_task,512,1,"idle_task\0");
  task_creatNewSysTask(testTask2,512,0,"testTask2\0");
  task_creatNewSysTask(testTask3,512,0,"testTask3\0");
  sched_startScheduler();
  while(1)
  {

  }
  return 0;
}

