/*
 * @Author Shi Zhangkun
 * @Date 2020-10-25 04:09:33
 * @LastEditTime 2022-04-27 20:47:55
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/fs/device.h
 */

#ifndef __DEVICE_H
#define __DEVICE_H

#include "yogaOS/types.h"
#include "yogaOS/hmap.h"

#define GET_MAIN_DEV_NUM(dev) ((dev >> 8)&(0xFF))
#define GET_SEC_DEV_NUM(dev) ((dev)&(0xFF))
#define SET_MAIN_DEV_NUM(dev, major) ((dev&0xFF)|((major&0xFF)<<8))
#define SET_SEC_DEV_NUM(dev, sec) ((dev&0xFF00)|(sec&0xFF))

#define MAIN_DEV_NUM_SIZE 0xFF
#define MAIN_SEC_NUM_SIZE 0xFF

struct device;
struct blockDevice;
typedef uint16_t devNumber_t;
typedef struct device device_t;
/* device operate code */
typedef enum {
  DEV_OPEN,
  DEV_READ,
  DEV_WRITE,
  DEV_CLOSE
}devOprType_t;

/* device type */
typedef enum {
  SERI_DEV,
  BLK_DEV
}devType_t;

/* device */
struct device {
  char* name;
  devType_t type;
  pid_t serv;
  devNumber_t number;
  mapItem_t item;
};

error_t dev_initManager(void);
device_t* dev_register(char* name, int major, pid_t serv, devType_t type);
error_t dev_remove(devNumber_t device);

#endif