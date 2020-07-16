/*
 * @Author Shi Zhangkun
 * @Date 2020-03-08 00:32:21
 * @LastEditTime 2020-05-19 01:24:56
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/driver/io.h
 */
#ifndef __IO_H
#define __IO_H
#include "yogaOS/types.h"
inline void  __enableIRQ(void){__asm__("sti"::);}
inline void  __disableIRQ(void){__asm__("cli"::);}

inline void IO_outByte(uint8_t data, uint16_t port)
{
  __asm__("outb %%al, %%dx"
          :
          :"a"(data), "d"(port)
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