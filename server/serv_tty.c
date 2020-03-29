/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 20:09:53
 * @LastEditTime 2020-03-28 04:08:26
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/server/serv_tty.c
 */

#include "type.h"
#include "server.h"
#include "unistd.h"
#include "tty.h"

extern tty_t * pCurrentActiveTTY;
/**
 * @brief  
 * @note  tty global server task 
 * @param {type} none
 * @retval none
 */
void server_tty(void)
{
  uint32_t key;
  char temp;
  tty_init();
  while(1)
  {
    msleep(50); //注意！！！！！！后面开发完成IPC换成等待消息队列
    key = tty_decode(pCurrentActiveTTY);
    tty_process(key,pCurrentActiveTTY);
    while(queue_read(1,&temp,&pCurrentActiveTTY->outputQueue))
    {
      console_dispStr(&temp,1,pCurrentActiveTTY->consoleIndex, pCurrentActiveTTY->backColor, \
                      pCurrentActiveTTY->frontColor);
    }
  }
  
}