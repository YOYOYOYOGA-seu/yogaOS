/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 20:11:37
 * @LastEditTime 2022-05-07 17:35:56
 * @LastEditors Shi Zhangkun
 * @Description prototype of system server process function
 * @FilePath /project/include/server.h
 */
#ifndef __SERVER_H
#define __SERVER_H
#include "yogaOS/types.h"

/* ------------------------------------- server register --------------------------------------- */
error_t server_init(void);
error_t server_reg(char* name, pid_t pid);
error_t server_remove(char* name, pid_t pid);
int server_search(char* name);
#endif