/*
 * @Author Shi Zhangkun
 * @Date 2020-03-08 00:32:21
 * @LastEditTime 2020-10-31 06:02:44
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/driver/io.h
 */
#ifndef __IO_H
#define __IO_H
#include "yogaOS/types.h"
#include "errno.h"
#include "time.h"

#define IO_PIC1_0         0x20
#define IO_PIC1_1         0x21

#define IO_KB_WR_BUF      0x60
#define IO_KB_STAT_CTR    0x64

#define IO_PIC2_0         0xA0
#define IO_PIC2_1         0xA1

#define IO_VGA_MOR_R         0x3cc
#define IO_VGA_MOR_W         0x3c2
#define IO_VGA_ISR_0_R       0x3c2
#define IO_VGA_ISR_1_R       0x3da
#define IO_VGA_FCR_R         0x3ca
#define IO_VGA_FCR_W         0x3da
#define IO_VGA_VSER_W        0x3c3

#define IO_VGA_CRT_ADDR      0x3d4
#define IO_VGA_CRT_DATA      0x3d5

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

inline void IO_inByteStream(uint16_t port, uint8_t* buf, size_t size)
{
  __asm__("cld;rep;insb"
          :
          :"d"(port),"D"(buf),"c"(size)
          );
}

inline void IO_inWordStream(uint16_t port, uint16_t* buf, size_t size)
{
  __asm__("cld;rep ;insw" 
          :
          :"d"(port),"D"(buf),"c"(size)
          );
}

inline error_t IO_waitUntil(uint8_t data, uint8_t mask, uint16_t port)
{
  while((IO_inByte(port)&mask) != (data&mask));
  return ENOERR;
}

inline error_t IO_waitUntilFor(uint8_t data, uint8_t mask, uint16_t port, int timeout)
{
  unsigned int t = timeout + time_getTimeCount();
  while(t > time_getTimeCount())
  {
    if((IO_inByte(port)&mask) == (data&mask))
      return ENOERR;
  }
  return ETIME;
}

#endif