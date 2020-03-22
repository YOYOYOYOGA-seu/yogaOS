#include "type.h"
#include "init.h"
#include "sched.h"
#include "unistd.h"
#include "keyboard.h"
extern void disp_string32(char *info);
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



void server_tty(void)
{
  uint32_t scanCode[10];
  uint32_t count,i,j;
  char charBuff[11];
  while(10)
  {

    count = kb_read(10,scanCode);
    msleep(50);
    if(!count)
      continue;

    
    for(i = 0,j = 0;i<count;i++)
    {
      if(scanCode[i] == 0xE1)
      {

      }
      else if(scanCode[i] == 0xE0)
      {

      }
      else
      {
        if(scanCode[i]&FLAG_BREAK)
        {

        }
        else
        {
          if(scanCode[i] < NR_SCAN_CODES)
          {
            charBuff[j] = keymap[scanCode[i] * MAP_COLS];
            j++;
          }
          
        }
        
      }
    }
    charBuff[j] = '\0';
    disp_string32(charBuff);
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
  task_creatNewSysTask(server_tty,512,0,"testTask3\0");

  sched_startScheduler();
  while(1)
  {

  }
  return 0;
}

