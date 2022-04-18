/*
 * @Author Shi Zhangkun
 * @Date 2020-10-17 00:19:27
 * @LastEditTime 2022-04-18 16:35:47
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/server/serv_hd.c
 */

#include "yogaOS/types.h"
#include "yogaOS/serv.h"
#include "unistd.h"
#include "yogaOS/req.h"
#include "hd.h"
#include "errno.h"
#define SERVER_HD_NAME "SERV_HD"
/**
 * @brief  this server handler the request which read block from hard disk
 * @note  request structure : req.pMsg:start block    req.type:opreate and block num
 * @param {type} none
 * @retval none
 */
void server_hd(void)
{
  request_t req;
  uint32_t type;
  hd_init();
  serv_reg(SERVER_HD_NAME);
  while (1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
  }
  serv_remove(SERVER_HD_NAME);
  
}
