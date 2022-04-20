#include "yogaOS/types.h"
#include "init.h"
#include "sched.h"
#include "server.h"
#include "stdlib.h"
#include "yogaOS/queue.h"
#include "unistd.h"
#include "stdio.h"
#include "yogaOS/req.h"
#include "kernel.h"
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
  request_t test1;
  int * test= (int *)0x20400000;
  
  while(1)
  {
    time++;
    test1.type = time;
    reqs(&test1,2);
    *test = time;
    printf("/033[0;31;44m req test:%d \n\r",test1.type);
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

void testMalloc(void)  // test task: malloc test
{
  int a = 1;
  void * ptr[10];
  heap_initMalloc();  //！！！！！ 注意应该改到fork函数中实现
  while(1)
  {
    
    for(int i = 0; i < 10; i++)
       ptr[i] = malloc(rand()%128 + 1);
    sleep(1);
    for(int i = 0; i < 10; i++)
      free(ptr[i]);
  }
  return;
}


/* 提醒：测试的时候需要注意现在只能使用优先级1、0, 大于1的优先级由于没有fork函数无法使用*/
int main(void){
  initBss();  // init the .bss of kernel segment (kernel's .bss segments must clear to 0 by yourself)
  initIRQ();
  initSysMsg();
  initMemManage();
  sched_initScheduler();
  init8254Timer();
  task_creatNewSysTask(init_task,512,1,10,"init_task\0");
  server_init();
  task_creatNewSysTask(idle_task,512,1,10,"idle_task\0");
  task_creatNewSysTask(testTask2,512,1,0,"testTask2\0");
  task_creatNewSysTask(testTask3,512,1,0,"testTask3\0");
  task_creatNewSysTask(testMalloc,512,1,0,"testMalloc\0");

  void* ptr1 = fmalloc(56464);
  void* ptr2 = fmalloc(32);
  void* ptr3 = fmalloc(56);
  void* ptr4 = fmalloc(75);
  void* ptr5 = fmalloc(12);

  ffree(ptr4);
  ffree(ptr5);
  ffree(ptr3);
  ffree(ptr2);
  ffree(ptr1);
  sched_startScheduler();
  while(1)
  {

  }
  return 0;
}

