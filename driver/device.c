/*
 * @Author Shi Zhangkun
 * @Date 2022-04-18 14:26:38
 * @LastEditTime 2022-05-04 14:31:37
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/driver/device.c
 */
#include "fs/device.h"
#include "yogaOS/hmap.h"
#include "yogaOS/req.h"
#include "string.h"
#include "stdlib.h"

hashMap_t deviceMap = HASH_MAP_WITH_INT_KEY(device_t,item);
miniList_t(mapItem_t) devMapBucket[MAIN_DEV_NUM_SIZE];

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @retval none
 */
static size_t hashFunc_deviceMap(hashMap_t* map, void * key)
{
  size_t num = (size_t)(key);
  return GET_MAIN_DEV_NUM(num);
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t dev_initManager(void)
{
  hashMap_init(&deviceMap, devMapBucket, sizeof(devMapBucket));
  hashMap_setHashFunction(&deviceMap, hashFunc_deviceMap);
}

/**
 * @brief  register device
 * @note  
 * @param {char*} name
 * @param {int} major : -1 means alloc 
 * @param {pid_t} serv
 * @param {devType_t} type
 * @retval none
 */
device_t* dev_register(char* name, int major, pid_t serv, devType_t type)
{
  device_t* ret = NULL;
  if (major < 0)
  {
    for (int i = 0; i < deviceMap.bucketSize; i++)
    {
      if (deviceMap.bucket[i].value == 0)
      {
        ret = malloc(sizeof(device_t));
        SET_MAIN_DEV_NUM(ret->number, i);
        SET_SEC_DEV_NUM(ret->number, 0);
        ret->serv = serv;
        ret->name = malloc(strlen(name));
        strcpy(ret->name, name);
        ret->type = type;
        break;
      }
    }
  }
  else if (major < deviceMap.bucketSize)
  {
    ret = malloc(sizeof(device_t));
    SET_MAIN_DEV_NUM(ret->number, major);
    ret->serv = serv;
    ret->name = malloc(strlen(name));
    strcpy(ret->name, name);
    ret->type = type;
    if (deviceMap.bucket[major].value == 0)
      SET_SEC_DEV_NUM(ret->number, 0);
    else
      SET_SEC_DEV_NUM(ret->number, GET_SEC_DEV_NUM((int)(deviceMap.bucket[major].firstItem->lru.pPrevious->key)) + 1);
  }

  if (ret)
  {
    if(deviceMap.put(&deviceMap, (void*)((int)(ret->number)), ret) != ENOERR)
    {
      free(ret);
      ret = NULL;
    }
  }
  return ret;
}

/**
 * @brief  remove one device by device number
 * @note  
 * @param {devNumber_t} major
 * @retval none
 */
error_t dev_remove(devNumber_t device)
{
  device_t* mach = deviceMap.get(&deviceMap, (void*)((int)device));
  if (mach != NULL)
  {
    deviceMap.remove(&deviceMap, (void*)((int)device));
    free(mach);
  }
  return ENOERR;
}

/**
 * @brief  defult device open function 
 * @note  
 * @param {pid_t} pid
 * @param {devNumber_t} dev
 * @retval none
 */
error_t dev_open_func(pid_t pid, devNumber_t dev)
{
  request_t req = {.type = (DEV_OPEN << sizeof(devNumber_t))&(dev), .length = 0, .pMesg = NULL};
  reqs(&req, pid);
  return req.type;
}

/**
 * @brief  defult device close function 
 * @note  
 * @param {pid_t} pid
 * @param {devNumber_t} dev
 * @retval none
 */
error_t dev_close_func(pid_t pid, devNumber_t dev)
{
  request_t req = {.type = (DEV_CLOSE << sizeof(devNumber_t))&(dev), .length = 0, .pMesg = NULL};
  reqs(&req, pid);
  return req.type;
}

/**
 * @brief  defult device write function 
 * @note  
 * @param {pid_t} pid
 * @param {devNumber_t} dev
 * @param {void*} content
 * @param {size_t} size
 * @retval none
 */
error_t dev_write_func(pid_t pid, devNumber_t dev, void* content, size_t size)
{
  request_t req = {.type = (DEV_WRITE << sizeof(devNumber_t))&(dev), .length = size, .pMesg = content};
  reqs(&req, pid);
  return req.type;
}

/**
 * @brief  defult device read function 
 * @note  
 * @param {pid_t} pid
 * @param {devNumber_t} dev
 * @param {void*} dest
 * @param {size_t} size
 * @retval none
 */
size_t dev_read_func(pid_t pid, devNumber_t dev, void* dest, size_t size)
{
  request_t req = {.type = (DEV_READ << sizeof(devNumber_t))&(dev), .length = size, .pMesg = dest};
  reqs(&req, pid);
  if(req.type != ENOERR) return 0;
  return req.length;
}