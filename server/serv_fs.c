/*
 * @Author Shi Zhangkun
 * @Date 2020-12-13 22:39:05
 * @LastEditTime 2020-12-13 22:39:06
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/server/serv_fs.c
 */

#include "vfs.h"
#include "yogaOS/req.h"
#include "yogaOS/types.h"
#include "errno.h"
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void server_hd(void)
{
  request_t req;
  uint32_t type;
  while (1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
  }
  
}