/*
 * @Author Shi Zhangkun
 * @Date 2022-04-18 15:56:48
 * @LastEditTime 2022-05-07 17:03:34
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/yogaOS/dev.h
 */
#ifndef __DEV_H
#define __DEV_H
#include "yogaOS/types.h"

#define GET_DEV_NUM(num) (dev&&0xFFFF)
#define GET_MAJOR_DEV_NUM(dev) ((dev >> 8)&(0xFF))
#define GET_SEC_DEV_NUM(dev) ((dev)&(0xFF))
#define SET_MAJOR_DEV_NUM(dev, major) dev = ((dev&0xFF)|((major&0xFF)<<8))
#define SET_SEC_DEV_NUM(dev, sec) dev = ((dev&0xFF00)|(sec&0xFF))

#define MAJOR_DEV_NUM_SIZE 0xFF
#define SEC_DEV_NUM_SIZE 0xFE

#define INVAILD_DEV_NUM  0xFFFF

typedef uint16_t devNumber_t;


/* device type */
typedef enum {
  SERIAL_DEV,
  BLK_DEV
}devType_t;

devNumber_t dev_regBlk(char* name, int major);
devNumber_t dev_regSerial(char* name, int major);
error_t dev_unreg(devNumber_t dev);

#endif