#include "type.h"
#include "init.h"
#include "sched.h"
#include "server.h"

#include "queue.h"
#include "unistd.h"
#include "stdio.h"
extern void initInterrupt(void);
int a = 1;
int b = 1;
char d = 'a';
char *c = &d;

void init_task(void)
{
  int a = 1;
  sleep(1);
  return;
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
  char buf[64];
  while(1)
  {
    time++;
    sprintf(buf,"test:%d %x",time,time);
    sleep(5);
  }
}

uint32_t test_queue[10];
queue_t test;
void testTask3(void) //test scheduler
{
  int i;
  int time = 0;
  pid_t pid;
  queue_init(10,4,test_queue,&test);
  uint32_t testbuff[10];
  while(1)
  {
    for(i = 0; i< 15; i++)
      queue_write(i,&test);
    time++;
    sleep(2);
    queue_read(3,testbuff,&test);
    pid = getpid();
  }
}



int main(void){
  init8254Timer();
  initInterrupt();
  initSysMsg();
  initMemManage();
  sched_initScheduler();
  task_creatNewSysTask(init_task,512,1,10,"init_task\0");
  task_creatNewSysTask(idle_task,512,1,10,"idle_task\0");
  task_creatNewSysTask(testTask2,512,0,0,"testTask2\0");
  task_creatNewSysTask(testTask3,512,0,15,"testTask3\0");
  task_creatNewSysTask(server_tty,512,0,0,"testTask3\0");

  sched_startScheduler();
  while(1)
  {

  }
  return 0;
}

