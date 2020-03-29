/*
 * @Author Shi Zhangkun
 * @Date 2020-03-21 03:48:55
 * @LastEditTime 2020-03-28 02:01:22
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/driver/tty.h
 */
#ifndef __TTY_H
#define __TTY_H

#include "type.h"
#include "keyboard.h"
#include "queue.h"
#include "console.h"
#include "sched.h"

#define SYS_TTY_NUM              3
#define TTY_CHAR_BUFF_SIZE       64
#define TTY_OUTPUT_BUFF_SIZE     64

#define TTY_OP_IDLE              0
#define TTY_OP_TASK_READING      1
#define TTY_OP_SHOWING           2

#define TTY_TYPE_STD             0xE1
#define TTY_TYPE_SERIAL          0xE2
#define TTY_TYPE_VIRTUAL         0xE3
typedef struct{
  char charBuff[TTY_CHAR_BUFF_SIZE];
  char outputBuff[TTY_OUTPUT_BUFF_SIZE];
  
  uint32_t cbCount;
  queue_t outputQueue;
  /*
  uint32_t cHead;
  uint32_t cTail;
  uint32_t oHead;
  uint32_t oTail;
  */
  uint32_t consoleIndex;
  
  
  pid_t readTask;   /* task wait for reading */
  uint32_t readNum; /* the num of char that the task want to read */

  uint32_t operateFlag;  /* 0 idle, 1 some task wait for reading , 2 outputing */ 

  uint32_t echoFlag;
  uint32_t flagNLCR;   /* if enter function key related to "\n\r", only used when input is keyboard(std tty) */

  uint32_t type;

  uint8_t backColor;
  uint8_t frontColor;
}tty_t;


void tty_init(void);
uint32_t tty_decode(tty_t * ptty);
void tty_process(uint32_t key,tty_t * ptty);
#endif