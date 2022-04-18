/*
 * @Author Shi Zhangkun
 * @Date 2022-04-18 15:56:48
 * @LastEditTime 2022-04-18 16:09:28
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/yogaOS/serv.h
 */
#ifndef __SERV_H
#define __SERV_H
#include "yogaOS/types.h"

error_t serv_reg(char* name);
error_t serv_remove(char* name);
pid_t serv_search(char* name);
#endif