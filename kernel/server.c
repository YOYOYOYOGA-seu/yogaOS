/*
 * @Author Shi Zhangkun
 * @Date 2022-04-18 16:05:00
 * @LastEditTime 2022-05-06 22:02:23
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/kernel/server.c
 */
#include "server.h"
#include "sched.h"
#include "yogaOS/hmap.h"
#include "kernel.h"
#include "string.h"

typedef struct {
  char* name;
  pid_t pid;
  mapItem_t item;
}serverItem_t;

hashMap_t serverMap = HASH_MAP_WITH_STR_KEY(serverItem_t, item);
hashMapBucket_t bucket[64];

extern void server_test(void);
extern void server_tty(void);
extern void server_hd(void);
extern void server_FS(void);

/**
 * @brief  init server register
 * @note  
 * @param {*}
 * @retval none
 */
error_t server_init()
{
  hashMap_init(&serverMap, bucket, sizeof(bucket));
  task_creatNewSysTask(server_FS,512,0,0,"server_fs\0");
  task_creatNewSysTask(server_tty,512,0,0,"server_tty\0");
  task_creatNewSysTask(server_test,512,0,0,"server_test\0");
  task_creatNewSysTask(server_hd,512,0,0,"server_hd\0");
  return ENOERR;
}

/**
 * @brief  add a server to register
 * @note  
 * @param {char*} name
 * @param {pid_t} pid
 * @retval none
 */
error_t server_reg(char* name, pid_t pid)
{
  serverItem_t* item = kmalloc(sizeof(serverItem_t));
  item->name = kmalloc(strlen(name));
  strcpy(item->name, name);
  item->pid = pid;
  return serverMap.put(&serverMap, item->name, item);
}

/**
 * @brief  remove a server from register
 * @note  
 * @param {char*} name
 * @param {pid_t} pid
 * @retval none
 */
error_t server_remove(char* name, pid_t pid)
{
  serverItem_t* item = serverMap.get(&serverMap,name);
  if (!item)
  {
    if (item->pid != pid) return EINVAL;
    serverMap.remove(&serverMap, name);
    kfree(item->name);
    kfree(item);
  }
  return ENOERR;
}

/**
 * @brief  get a server's pid
 * @note  
 * @param {char*} name
 * @retval none
 */
pid_t server_search(char* name)
{
  serverItem_t* item = serverMap.get(&serverMap,name);
  if (!item)
  {
    return item->pid;
  }
  return 0;
}