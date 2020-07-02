/*
 * @Author Shi Zhangkun
 * @Date 2020-03-27 06:26:26
 * @LastEditTime 2020-03-27 09:26:36
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/queue.h
 */
#ifndef __QUEUE_H
#define __QUEUE_H
#include "types.h"
typedef struct
{
  void *queue;    /* point to the queue buff */
  void *head;     
  void *tail;
  unsigned int unitSize; /* item size of queue, can be 1(byte),2(word),4(dword)  */
  unsigned int size;
  unsigned int count;
}queue_t; /* Only support small end */

error_t queue_init(unsigned int size, unsigned int unitSize, void * base, queue_t *q);
unsigned int queue_read(unsigned int num, void *buff, queue_t *q);
error_t queue_write(unsigned long item,queue_t *q);
#endif