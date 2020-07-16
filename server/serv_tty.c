/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 20:09:53
 * @LastEditTime 2020-06-25 05:51:33
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/server/serv_tty.c
 */
#include "yogaOS/types.h"
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
  int i,count;
  
  tty_init();
  while(1)
  {
    msleep(50); //注意！！！！！！后面开发完成IPC换成等待消息队列
    key = tty_decode(pCurrentActiveTTY);
    tty_process(key,pCurrentActiveTTY);
    for(i = 0;i<SYS_TTY_NUM; i++)
    {
      tty_outputData(i);
      
    }
    
  }
  
}