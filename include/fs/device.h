/*
 * @Author Shi Zhangkun
 * @Date 2020-10-25 04:09:33
 * @LastEditTime 2022-05-06 21:45:56
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/fs/device.h
 */

#ifndef __DEVICE_H
#define __DEVICE_H

#include "yogaOS/types.h"
#include "yogaOS/hmap.h"
#include "yogaOS/serv.h"
#include "yogaOS/dev.h"



struct device;
struct blockDevice;
typedef struct device device_t;
/* device operate code */
#define DEV_OPEN SERV_DEF_OPEN
#define DEV_CLOSE SERV_DEF_CLOSE
#define DEV_READ SERV_DEF_READ
#define DEV_WRITE SERV_DEF_WRITE

#define GET_DEV_OPR_TYPE GET_SERV_OPR_TYPE
#define GET_DEV_OPR_ARG  GET_SERV_OPR_ARG
#define SET_DEV_REQ_TYPE SET_SERV_REQ_TYPE


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
error_t dev_unregister(devNumber_t device);

#endif