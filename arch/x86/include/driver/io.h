/*
 * @Author Shi Zhangkun
 * @Date 2020-03-08 00:32:21
 * @LastEditTime 2020-03-21 06:35:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/driver/io.h
 */
#ifndef __IO_H
#define __IO_H
#include "type.h"

inline void IO_outByte(uint8_t data, uint16_t port)
{
  __asm__("outb %0, %%dx"
          :
          :"q"(data), "d"(port)
          );
}

inline uint8_t IO_inByte(uint16_t port)
{
  uint8_t data;
  __asm__("inb %%dx, %0"
          :"=a"(data)
          :"d"(port)
          );
  return data;
}

#endif