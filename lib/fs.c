/*
 * @Author Shi Zhangkun
 * @Date 2020-04-04 05:37:54
 * @LastEditTime 2020-04-04 07:13:54
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/fs.c
 */

#include "unistd.h"

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);
ssize_t write (int fd,const void * buf,size_t count)
{
  
  enterSystemCall(SYS_WRITE_VECTOR,(int)fd, (int)buf, (int)count);
}

