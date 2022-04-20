/*
 * @Author Shi Zhangkun
 * @Date 2022-04-14 21:01:03
 * @LastEditTime 2022-04-19 03:32:23
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/hmap.c
 */
#include "yogaOS/list.h"
#include "yogaOS/hmap.h"
#include "string.h"

static error_t default_putFunc(hashMap_t* map, void * key, void* value);
static void* default_getFunc(hashMap_t* map, void * key);
static void default_rmFunc(hashMap_t* map, void * key);
static int default_extFunc(hashMap_t* map, void * key);
static void default_clearFunc(hashMap_t* map);

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void*} mem
 * @param {size_t} size
 * @retval none
 */
error_t hashMap_init(hashMap_t* map, void* mem, size_t size)
{

  if (!map || !mem || !size) return EFAULT;
  *(size_t*)(&map->size) = 0;
  *(size_t*)(&map->bucketSize) = size/sizeof(*map->bucket);
  *(miniList_t(mapItem_t)**)(&map->bucket) = mem;
  *(putFunc_t*)(&map->put) = default_putFunc;
  *(getFunc_t*)(&map->get) = default_getFunc;
  *(rmFunc_t*)(&map->remove) = default_rmFunc;
  *(clearFunc_t*)(&map->clear) = default_clearFunc;
  *(extFunc_t*)(&map->exists) = default_extFunc;
  for (int i = 0; i < map->bucketSize; i++)
  {
    miniList_init(&map->bucket[i]);
  }
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {hashFunc_t} func
 * @retval none
 */
error_t hashMap_setHashFunction(hashMap_t* map, hashFunc_t func)
{
  if (!func) return EFAULT;
  *(hashFunc_t*)(&map->hashCode) = func;
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {equalFunc_t} func
 * @retval none
 */
error_t hashMap_setEqualFunction(hashMap_t* map, equalFunc_t func)
{
  if (!func) return EFAULT;
  *(equalFunc_t*)(&map->equal) = func;
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {size_t} index
 * @param {void*} key
 * @retval none
 */
static mapItem_t* __getFromList(hashMap_t* map, size_t index, void* key) 
{
  mapItem_t* matchRes = NULL;
  miniList_matchByFunc(&map->bucket[index], matchRes, map->equal, key, key, lru);
  return matchRes;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @retval none
 */
size_t default_hashFunc_int(hashMap_t* map, void * key)
{
  size_t num = (size_t)(key);
  return num;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @retval none
 */
size_t default_hashFunc_string(hashMap_t* map, void * key)
{
  size_t num = 0;
  char* c = key;
  while (*c != '\0')
  {
    num = num*(0x7F - '0') + (*c - '0');
    c++;
  }
  return num;
}

/**
 * @brief  
 * @note  
 * @param {void *} key1
 * @param {void *} key2
 * @retval none
 */
int default_equalFunc_int(void * key1, void * key2)
{
  return (size_t)(key1) == (size_t)(key2);
}

/**
 * @brief  
 * @note  
 * @param {void *} key1
 * @param {void *} key2
 * @retval none
 */
int default_equalFunc_string(void * key1, void * key2)
{
  return strcmp(key1, key2);
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @param {void*} value
 * @retval none
 */
error_t default_putFunc(hashMap_t* map, void * key, void* value)
{
  if (!map) return EFAULT;
  mapItem_t* item = (mapItem_t*)(value + map->offset);
  item->key = key;
  size_t index = map->hashCode(map, item->key)%map->bucketSize;
  if (__getFromList(map, index, item->key)) return E_HMAP_KEY_EXIST;
  miniList_insertHead(&map->bucket[index], item, lru);
  return ENOERR;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @retval none
 */
void* default_getFunc(hashMap_t* map, void * key)
{
  if (!map) return NULL;
  size_t index = map->hashCode(map, key);
  void* item = __getFromList(map, index%map->bucketSize, key);
  return (void*)(item != NULL ? item - map->offset : NULL);
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @retval none
 */
void default_rmFunc(hashMap_t* map, void * key)
{
  if (!map) return;
  size_t index = map->hashCode(map, key);
  mapItem_t* matchRes = __getFromList(map, index%map->bucketSize, key);
  if (matchRes)
  {
    miniList_remove(&map->bucket[index%map->bucketSize], matchRes, lru);
  }
  return;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @param {void *} key
 * @retval none
 */
int default_extFunc(hashMap_t* map, void * key)
{
  if (!map) return 1;
  mapItem_t* matchRes = map->get(map, key);
  return matchRes != NULL;
}

/**
 * @brief  
 * @note  
 * @param {hashMap_t*} map
 * @retval none
 */
void default_clearFunc(hashMap_t* map)
{
  return;
}