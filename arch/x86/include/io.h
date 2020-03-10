/*
 * @Author Shi Zhangkun
 * @Date 2020-03-08 00:32:21
 * @LastEditTime 2020-03-08 00:45:50
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/io.h
 */
#ifndef __IO_H
#define __IO_H
#include "type.h"
extern inline void IO_outByte(uint8_t data, uint16_t port)
{
  __asm__("outb %0, %%dx"
          :
          :"q"(data), "d"(port)
          );
}


#endif