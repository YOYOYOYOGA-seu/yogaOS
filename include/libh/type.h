/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 22:12:51
 * @LastEditTime 2020-04-04 05:53:42
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/type.h
 */
#ifndef __TYPE_H
#define __TYPE_H


typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;

typedef uint32_t pid_t; 

typedef int error_t;

typedef int ssize_t;
typedef unsigned int size_t;

typedef enum{
  SYS_EXIT_VECTOR = 0,
  SYS_FORK_VECTOR,
  SYS_SLEEP_VECTOR,
  SYS_WAIT_VECTOR,
  SYS_KILL_VECTOR,
  SYS_EXCVE_VECTOR,
  SYS_GET_PID_VECTOR,
  SYS_GET_TIME_VECTOR,
  
  SYS_WRITE_VECTOR,
  SYS_READ_VECTOR,
  SYS_OPEN_VECTOR
}syscall_vector_t;

#define NULL (void *)0
#endif