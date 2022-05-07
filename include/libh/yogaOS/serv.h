/*
 * @Author Shi Zhangkun
 * @Date 2022-04-18 15:56:48
 * @LastEditTime 2022-05-06 21:42:33
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/yogaOS/serv.h
 */
#ifndef __SERV_H
#define __SERV_H
#include "yogaOS/types.h"

#define GET_SERV_OPR_TYPE(reqType) ((uint8_t)(reqType&0xFF))
#define GET_SERV_OPR_ARG(reqType)  ((uint32_t)((reqType >> 8)&0xFFFFFF))
#define SET_SERV_REQ_TYPE(type, arg) (((uint32_t)type&0xFF) | (((uint32_t)arg << 8)&0xFFFFFF00))
typedef enum {
  SERV_DEF_READ,
  SERV_DEF_WRITE,
  SERV_DEF_OPEN,
  SERV_DEF_CLOSE,
  SERV_DEF_REG,
  SERV_DEF_UNREG
}servOprType_t;


/* server task oprate */
error_t serv_reg(char* name);
error_t serv_remove(char* name);
pid_t serv_search(char* name);

void sfree(void *ptr); //free shared area
void* smalloc(size_t size); //alloc a shared area(shared by all system server)
#endif