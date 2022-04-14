/*
 * @Author Shi Zhangkun
 * @Date 2020-12-13 22:39:05
 * @LastEditTime 2022-04-14 21:25:18
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/server/serv_fs.c
 */

#include "fs/vfs.h"
#include "yogaOS/req.h"
#include "yogaOS/types.h"
#include "errno.h"
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void server_VFS(void)
{
  request_t req;
  uint32_t type;
  fcache_init();
  while (1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
  }
  
}