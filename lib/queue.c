/*
 * @Author Shi Zhangkun
 * @Date 2020-03-27 06:25:32
 * @LastEditTime 2020-03-27 07:27:36
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/queue.c
 */
#include "queue.h"
#include "errno.h"
#include "type.h"

error_t queue_init(unsigned int size, unsigned int unitSize, void * base, queue_t *q)
{
  if(base == NULL)
    return E_QUEUE_NULL_P;
  q->count = 0;
  q->head = base;
  q->tail = base;
  q->queue = base;
  q->size = size;
  q->unitSize = unitSize;
}
unsigned int queue_read(unsigned int num, void *buff, queue_t *q)
{
  uint32_t count = 0,i;
  char temp;
  while(q->count > 0 && count < num)
  {
    for(i=0;i<q->unitSize;i++)
    {
      temp =  *((char*)q->tail + i);
      *(char*)(buff) = temp;   //write buff
      buff = (void*)((unsigned int)buff + 1);
    }
    if((unsigned int)q->tail <= (unsigned int)q->queue + (q->size-2)*q->unitSize)       //if reach the top addr of buff
      q->tail = (void*)((unsigned int)q->tail + q->unitSize);
    else
      q->tail = q->queue;


    q->count --;
    count ++;
  }
  return count;
}
error_t queue_write(unsigned long item, queue_t *q)
{
  int i;
  char temp;
  if(q->count < q->size)
  {
    for(i=0;i<q->unitSize;i++)
    {
      temp = (char)item>>(i*8)&0xff;
      *((char*)q->head + i) = temp;   //write buff
    }
    if((unsigned int)q->head <= (unsigned int)q->queue + (q->size-2)*q->unitSize)       //if reach the top addr of buff
      q->head = (void*)((unsigned int)q->head + q->unitSize);
    else
      q->head = q->queue;

    q->count ++;
  }
  else 
  {
    return E_QUEUE_FULL;
  }
  return ENOERR;
}