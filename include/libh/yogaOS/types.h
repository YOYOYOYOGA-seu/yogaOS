/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 22:12:51
 * @LastEditTime 2020-11-15 04:56:47
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/yogaOS/types.h
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
  SYS_REQUEST = 0,
  SYS_EXIT_VECTOR,
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



typedef struct {
  /* data */
    union {
      pid_t ownerPid;
      uint8_t it;   
    };
    uint32_t type;
    uint32_t length;  //length of data in pMesg, uint is byte
    void *pMesg;      //！！！！！由于没有写共享内存空间或文件系统，这个版本不能使用，尽量用type实现信息传输,或使用result[]回复小量信息
 
  
}request_t;

#define NULL (void *)0
#endif