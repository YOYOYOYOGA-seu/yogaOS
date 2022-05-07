/*
 * @Author Shi Zhangkun
 * @Date 2020-12-13 22:39:05
 * @LastEditTime 2022-05-06 21:57:19
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/server/serv_fs.c
 */

#include "fs/vfs.h"
#include "fs/device.h"
#include "yogaOS/req.h"
#include "yogaOS/types.h"
#include "yogaOS/hmap.h"
#include "yogaOS/serv.h"
#include "errno.h"

#define SERVER_FS_NAME "SERV_FS"

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void server_FS(void)
{
  request_t req;
  uint8_t type;
  fcache_init();
  dev_initManager();
  serv_reg(SERVER_FS_NAME);
  while (1)
  {
    if(reqw(&req)!= ENOERR)
      continue;
    type = GET_SERV_OPR_TYPE(req.type);
    switch (type)
    {
    case SERV_DEF_REG:
    {
      devType_t devType = (GET_DEV_OPR_ARG(req.type) >> 16) & 0xFF;
      int major = GET_DEV_OPR_ARG(req.type) & 0xFFFF; 
      device_t* dev = dev_register(req.pMesg, major > MAJOR_DEV_NUM_SIZE ? -1 : major, req.ownerPid, devType == BLK_DEV ? BLK_DEV : SERIAL_DEV);
      if (dev)
      {
        req.type = SET_SERV_REQ_TYPE(type, dev->number);
      }
      else
      {
        req.type = SET_SERV_REQ_TYPE(type, INVAILD_DEV_NUM);
      }
      req.pMesg = NULL;
      req.length = 0;
      reqa(&req);
      break;
    }
    case SERV_DEF_UNREG:
    { 
      devNumber_t dev = GET_DEV_NUM(GET_DEV_OPR_ARG(req.type));
      if(dev_unregister(dev) != ENOERR)
      {
        req.type = SET_SERV_REQ_TYPE(type, INVAILD_DEV_NUM);
      }
      else
      {
        req.type = SET_SERV_REQ_TYPE(type, 0);
      }
      req.pMesg = NULL;
      req.length = 0;
      reqa(&req);
      break;
    }

    default:
      break;
    }
  }
  serv_remove(SERVER_FS_NAME);
}