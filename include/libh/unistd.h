/*
 * @Author Shi Zhangkun
 * @Date 2020-03-09 01:00:29
 * @LastEditTime 2020-03-09 05:06:54
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/unistd.h
 */
#ifndef __UNISTD_H
#define __UNISTD_H
#include "type.h"

void exit(int __status);  //__status :message sent to it's father proccess
pid_t fork(void);
pid_t getpid(void);
unsigned sleep(unsigned int __seconds);
unsigned usleep(unsigned int __useconds);
unsigned msleep(unsigned int __microsecond);
int execve(const char *__path, char * const __argv[], char * const __envp[] );
#endif