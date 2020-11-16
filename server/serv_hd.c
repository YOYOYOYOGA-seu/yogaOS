/*
 * @Author Shi Zhangkun
 * @Date 2020-10-17 00:19:27
 * @LastEditTime 2020-11-15 10:05:04
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/server/serv_hd.c
 */

#include "yogaOS/types.h"
#include "server.h"
#include "unistd.h"
#include "yogaOS/req.h"
#include "hd.h"
#include "errno.h"

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
  while (1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
  }
  
}
