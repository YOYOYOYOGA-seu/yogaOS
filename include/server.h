/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 20:11:37
 * @LastEditTime 2022-04-18 16:41:03
 * @LastEditors Shi Zhangkun
 * @Description prototype of system server process function
 * @FilePath /yogaOS/include/server.h
 */
#ifndef __SERVER_H
#define __SERVER_H
#include "yogaOS/types.h"
/* ------------------------------------- server process func --------------------------------------- */

void server_VFS(void);
/* ------------------------------------- server register --------------------------------------- */
error_t server_init(void);
error_t server_reg(char* name, pid_t pid);
error_t server_remove(char* name, pid_t pid);
pid_t server_search(char* name);
#endif