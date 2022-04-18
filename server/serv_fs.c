/*
 * @Author Shi Zhangkun
 * @Date 2020-12-13 22:39:05
 * @LastEditTime 2022-04-18 16:36:02
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/server/serv_fs.c
 */

#include "fs/vfs.h"
#include "yogaOS/req.h"
#include "yogaOS/types.h"
#include "yogaOS/hmap.h"
#include "yogaOS/serv.h"
#include "errno.h"

#define SERVER_VFS_NAME "SERV_VFS"
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
  serv_reg(SERVER_VFS_NAME);
  while (1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
  }
  serv_remove(SERVER_VFS_NAME);
}