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

static uint32_t keyState;


void server_tty(void)
{
  uint32_t scanCode[10];
  uint32_t count,i,j;
  char charBuff[11];
  uint32_t flag_E0;
  uint32_t make;
  uint32_t column;
  uint32_t key;
  while(1)
  {

    count = kb_read(10,scanCode);
    msleep(50);   /*    注意！！！！！！！！！！在后期加入IPC功能后，改为等待信号量，在键盘中断中投喂信号量  */
    if(!count)
      continue;

    
    for(i = 0,j = 0;i<count;i++)
    {
      if(scanCode[i] == 0xE1)   //PAUSE key(don't support yet)
      {

      }
      else if(scanCode[i] == 0xE0)// PrintScreen(don't support yet) or other(F1, F2,ESC....)
      {
        if(i == count + 1)  // need ready form keyboard buff
        {
          while(!kb_read(1,&scanCode[i]))
            msleep(50);                 /*    注意！！！！！！！！！！在后期加入IPC功能后，改为等待信号量，在键盘中断中投喂信号量  */
        }
        else
        {
          i++;     //0xE0 0xXX two code make up a key
        }
        
        flag_E0 = 1;
      }
      if(1/* key != PRINTSCREEN && key != PAUSE */)
      {
        make = (scanCode[i] & FLAG_BREAK ? 0:1);

        column = 0;
        if(keyState&FLAG_SHIFT_L || keyState&FLAG_SHIFT_R)
          column = 1;
        if(flag_E0)
        {
          column = 2;     
          flag_E0 = 0;
        }
        key =  keymap[(scanCode[i]&0x7F) * MAP_COLS + column];                                      // make code
        switch (key)
        {
        case SHIFT_L:
          make ? (keyState |= FLAG_SHIFT_L ): (keyState &= ~FLAG_SHIFT_L);
          key = 0;
          break;
        case SHIFT_R:
          make ? (keyState |= FLAG_SHIFT_R) : (keyState &= ~FLAG_SHIFT_R);
          key = 0;
          break;
        case ALT_L:
          make ? (keyState |= FLAG_ALT_L) : (keyState &= ~FLAG_ALT_L);
          key = 0;
          break;
        case ALT_R:
          make ? (keyState |= FLAG_ALT_R) : (keyState &= ~FLAG_ALT_R);
          key = 0;
          break;
        case CTRL_L:
          make ? (keyState |= FLAG_CTRL_L) : (keyState &= ~FLAG_CTRL_L);
          key = 0;
          break;
        case CTRL_R:
          make ? (keyState |= FLAG_CTRL_R) : (keyState &= ~FLAG_CTRL_R);
          key = 0;
          break;

        default:     //if notbreak code
          if(!make)
            key = 0;
          break;
        }
        if(key)  //is a code 
        {
          charBuff[j] = key;
          j++;
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

