/*
 * @Author Shi Zhangkun
 * @Date 2020-05-19 03:29:27
 * @LastEditTime 2022-04-18 16:35:42
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/server/serv_test.c
 */ 

#include "yogaOS/types.h"
#include "yogaOS/serv.h"
#include "unistd.h"
#include "yogaOS/req.h"
#include "errno.h"

#define SERVER_TEST_NAME "SERV_TEST"

/**
 * @brief  
 * @note  tty global server task 
 * @param {type} none
 * @retval none
 */
void server_test(void)
{
  request_t req;
  while(1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
    sleep(2);
    serv_reg(SERVER_TEST_NAME);
    switch (req.type)
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
  serv_remove(SERVER_TEST_NAME);
}