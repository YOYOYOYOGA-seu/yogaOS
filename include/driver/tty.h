/*
 * @Author Shi Zhangkun
 * @Date 2020-03-21 03:48:55
 * @LastEditTime 2020-06-25 06:06:32
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/driver/tty.h
 */
#ifndef __TTY_H
#define __TTY_H

#include "yogaOS/types.h"
#include "keyboard.h"
#include "yogaOS/queue.h"
#include "console.h"

/* ------------------------------------- define --------------------------------------- */
#define SYS_TTY_NUM              3
#define TTY_CHAR_BUFF_SIZE       64
#define TTY_OUTPUT_BUFF_SIZE     64

#define TTY_OP_IDLE              0
#define TTY_OP_TASK_READING      1
#define TTY_OP_SHOWING           2

#define TTY_TYPE_STD             0xE1
#define TTY_TYPE_SERIAL          0xE2
#define TTY_TYPE_VIRTUAL         0xE3
/* ----------------------------- tty attribute flag define --------------------------------- */
#define TTY_FLAG_ECHO            0x0001  /* echo */
#define TTY_FLAG_NLCR            0x0002  /* if enter function key related to "\n\r", only used when input is keyboard(std tty) */
#define TTY_FLAG_BS_GLOBAL           0x0004  /* if CTR_ON bit = 1, tty will handler the backspace key, else tty will regard it as a ascii */
/* ------------------------------------- typedef --------------------------------------- */
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
  uint32_t ttyIndex;
  
  pid_t readTask;   /* task wait for reading */
  uint32_t readNum; /* the num of char that the task want to read */

  uint32_t operateFlag;  /* 0 idle, 1 some task wait for reading , 2 outputing */ 

  uint32_t flagNLCR;  

  uint32_t flag;

  uint32_t type;

  uint8_t backColor;   /* defualt back color */
  uint8_t frontColor;   /* defualt front color */

  uint8_t backColorTemp;  /* temp back color, would be reset to 0xFF after outputBuff clear */
  uint8_t frontColorTemp; /* temp front color, would be reset to 0xFF after outputBuff clear */
}tty_t;

/* --------------------------------- function declear ---------------------------- */
void tty_init(void);
uint32_t tty_decode(tty_t * ptty);
void tty_process(uint32_t key,tty_t * ptty);
int tty_write(int ttyNum, char *buf, int count);
void tty_outputData(int ttyNum);
#endif