/*
 * @Author Shi Zhangkun
 * @Date 2020-05-19 03:29:27
 * @LastEditTime 2020-06-27 08:18:58
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/server/serv_test.c
 */ 

#include "types.h"
#include "server.h"
#include "unistd.h"
#include "req.h"


/**
 * @brief  
 * @note  tty global server task 
 * @param {type} none
 * @retval none
 */
void server_test(void)
{
  request_t req;
  uint32_t type;
  while(1)
  {
    type = reqw(&req);
    sleep(2);
    switch (type)
    {
    case 0:
      req.type = 10;
      reqa(&req);
      break;
    case 1:
      req.type = 11;
      reqa(&req);
      break;
    default:
      req.type += 100;
      reqa(&req);
      break;
    }
   
  }
  
}