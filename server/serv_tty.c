/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 20:09:53
 * @LastEditTime 2022-04-18 16:35:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/server/serv_tty.c
 */
#include "yogaOS/types.h"
#include "yogaOS/serv.h"
#include "unistd.h"
#include "tty.h"

#define SERVER_TTY_NAME "SERV_TTY"

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
  serv_reg(SERVER_TTY_NAME);
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
  serv_remove(SERVER_TTY_NAME);
}