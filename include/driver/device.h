/*
 * @Author Shi Zhangkun
 * @Date 2020-10-25 04:09:33
 * @LastEditTime 2020-10-25 04:31:06
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/driver/device.h
 */

#ifndef __DEVICE_H
#define __DEVICE_H

#include "yogaOS/types.h"

typedef struct blockDevice{
  uint8_t devID;
  uint8_t devID_s;
  uint8_t type;

  uint8_t blockSize;
  error_t (*initDevice)(struct blockDevice *dev);
  error_t (*deInitDevice)(struct blockDevice *dev);
  error_t (*readBlock)(struct blockDevice *dev, uint32_t start, uint32_t num, uint8_t* buf);
  error_t (*writeBlock)(struct blockDevice *dev, uint32_t start, uint32_t num, uint8_t* buf);

}blockDevice_t;

#endif