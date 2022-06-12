/*
 * @Author Shi Zhangkun
 * @Date 2020-10-24 21:16:06
 * @LastEditTime 2022-06-12 14:48:32
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/driver/block/hd.c
 */
#include "yogaOS/dev.h"
#include "hd.h"
#include "errno.h"
#include "string.h"
#include "stdlib.h"

hd_t hdDevVector[MAX_HD_NUM] = {0};

int hdCounts;
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t hd_init(void)
{
  hdCounts = hd_controllerInit(hdDevVector);
  if(hdCounts > 0)
  {
    char devName[] = {'s', 'd', 'a', '\0'};
    for (int i = 0; i < hdCounts; i++)
    {
      static uint8_t mbr[HD_LOGIC_SECTOR_SIZE];
      hdOperate_t ctl = {.secSize = HD_LOGIC_SECTOR_SIZE, 
                         .counts = 1,
                         .dest = mbr,
                         .startSec = 0 };
      if (hd_operate(&hdDevVector[i], ctl) < 0)
      {
        hdDevVector[i].valid = 0;
        continue;
      }
      memcpy(hdDevVector[i].dpt, &mbr[HD_MBR_DPT_OFFSET], sizeof(hdDevVector[i].dpt));
      hdDevVector[i].devNum = dev_regBlk(devName, -1);
      devName[2]++;  //sda -> sdb -> sdc ....
    }
  }
  return ENOERR;
}
