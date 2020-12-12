/*
 * @Author Shi Zhangkun
 * @Date 2020-10-24 21:16:06
 * @LastEditTime 2020-11-14 01:50:44
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/driver/block/hd.c
 */

#include "hd.h"
#include "device.h"
#include "errno.h"
hd_t hdDevVector[MAX_HD_NUM] = {0};

int hdDevNum;
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t hd_init(void)
{
  hdDevNum = hd_controllerInit(hdDevVector);
  if(hdDevNum > 0)
  {

  }
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
size_t hd_read()
{
  
}