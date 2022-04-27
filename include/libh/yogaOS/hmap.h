/*
 * @Author Shi Zhangkun
 * @Date 2022-04-14 14:33:27
 * @LastEditTime 2022-04-26 14:23:58
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/yogaOS/hmap.h
 */
#ifndef __HMAP_H
#define __HMAP_H
#include "errno.h"
#include "list.h"
#include "stddef.h"

struct mapItem;
struct hashMap;
typedef struct mapItem mapItem_t;
typedef struct hashMap hashMap_t;

struct mapItem {
  void* key;
  miniListItem_t(mapItem_t) lru;
};

typedef miniList_t(mapItem_t) hashMapBucket_t;

typedef size_t(*hashFunc_t)(hashMap_t* map, void * key);
typedef int(*equalFunc_t)(void * key1, void * key2);
typedef int(*lessFunc_t)(void * key1, void * key2);
typedef error_t(*putFunc_t)(hashMap_t* map, void * key, void* value);
typedef void*(*getFunc_t)(hashMap_t* map, void * key);
typedef void(*rmFunc_t)(hashMap_t* map, void * key);
typedef int(*extFunc_t)(hashMap_t* map, void * key);
typedef void(*clearFunc_t)(hashMap_t* map);
typedef void*(*allocFunc_t)(size_t size);
typedef void(*freeFunc_t)(void *ptr);

/*
 * hash map
 */
struct hashMap {
  const size_t size;                    //numbers of elements
  const size_t bucketSize;              //numbers of hash buckets
  const size_t offset;                  // for get the value ptr from mapItem_t
  miniList_t(mapItem_t)* const bucket;  // hash map
  hashFunc_t const hashCode;  // hash function
  equalFunc_t const equal;        // == funtion for elements
  lessFunc_t const less;         // < funtion for elements
  putFunc_t const put;            // put <key, value> (must be the setting type of this map)
  getFunc_t const get;            // get value by key
  rmFunc_t const remove;      // delete value by key
  clearFunc_t const clear;         
  extFunc_t const exists;      
};

#define HASH_MAP_WITH_INT_KEY(TYPE, ENTRYNAME) { \
            .size = 0, .bucketSize = 0, \
            .offset = offsetof(TYPE, ENTRYNAME),\
            .bucket = NULL, \
            .hashCode = default_hashFunc_int, \
            .equal = default_equalFunc_int \
            .less = default_lessFunc_int \
        }

#define HASH_MAP_WITH_STR_KEY(TYPE, ENTRYNAME) { \
            .size = 0, .bucketSize = 0, \
            .offset = offsetof(TYPE, ENTRYNAME),\
            .bucket = NULL, \
            .hashCode = default_hashFunc_string, \
            .equal = default_equalFunc_string, \
            .less = default_lessFunc_string \
        }

size_t default_hashFunc_int(hashMap_t* map, void * key);
int default_equalFunc_int(void * key1, void * key2);
int default_lessFunc_int(void * key1, void * key2);
size_t default_hashFunc_string(hashMap_t* map, void * key);
int default_equalFunc_string(void * key1, void * key2);
int default_lessFunc_string(void * key1, void * key2);


error_t hashMap_init(hashMap_t* map, void* mem, size_t size); 
error_t hashMap_setHashFunction(hashMap_t* map, hashFunc_t func);
error_t hashMap_setEqualFunction(hashMap_t* map, equalFunc_t func);
error_t hashMap_setLessFunction(hashMap_t* map, lessFunc_t func);
error_t hash_Map_deinit(hashMap_t* map);
#endif