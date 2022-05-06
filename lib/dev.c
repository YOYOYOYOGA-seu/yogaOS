/*
 * @Author Shi Zhangkun
 * @Date 2022-05-06 15:10:24
 * @LastEditTime 2022-05-06 21:54:17
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/lib/dev.c
 */

#include "yogaOS/dev.h"
#include "yogaOS/req.h"
#include "yogaOS/serv.h"
#include "errno.h"
#include "string.h"

/**
 * @brief  
 * @note  
 * @param {char*} name
 * @param {int} major
 * @retval none
 */
devNumber_t dev_regBlk(char* name, int major)
{
  devNumber_t dev;
  request_t req;
  pid_t pid = serv_search("SERVER_FS");
  uint32_t arg = (major&0xFFFF)|((BLK_DEV << 16)&0xFF0000);
  char* msg = NULL;
  req.type = SET_SERV_REQ_TYPE(SERV_DEF_REG, arg);
  req.length =strlen(name);
  msg = smalloc(req.length);
  strcpy(msg, name);
  req.pMesg = msg;
  reqs(&req, pid);
  arg = GET_SERV_OPR_ARG(req.type);
  sfree(msg);
  return GET_DEV_NUM(arg);
}

/**
 * @brief  
 * @note  
 * @param {char*} name
 * @param {int} major
 * @retval none
 */
devNumber_t dev_regSerial(char* name, int major)
{
  devNumber_t dev;
  request_t req;
  pid_t pid = serv_search("SERVER_FS");
  uint32_t arg = (major&0xFFFF)|((SERIAL_DEV << 16)&0xFF0000);
  char* msg = NULL;
  req.type = SET_SERV_REQ_TYPE(SERV_DEF_REG, arg);
  req.length =strlen(name);
  msg = smalloc(req.length);
  strcpy(msg, name);
  req.pMesg = msg;
  reqs(&req, pid);
  arg = GET_SERV_OPR_ARG(req.type);
  sfree(msg);
  return GET_DEV_NUM(arg);
}

/**
 * @brief  
 * @note  
 * @param {devNumber_t} dev
 * @retval none
 */
error_t dev_unreg(devNumber_t dev)
{
  request_t req;
  pid_t pid = serv_search("SERVER_FS");
  char* msg = NULL;
  req.type = SET_SERV_REQ_TYPE(SERV_DEF_REG, dev);
  req.length = 0;
  reqs(&req, pid);
  dev = GET_DEV_NUM(GET_SERV_OPR_ARG(req.type));
  if (dev == INVAILD_DEV_NUM)
    return ENODEV;
  return ENOERR;
}
