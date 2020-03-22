/*
 * @Author Shi Zhangkun
 * @Date 2020-02-29 04:35:35
 * @LastEditTime 2020-03-21 06:17:46
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/irq.h
 */
#ifndef __IRQ_H
#define __IRQ_H
#define TIME_IRQ_VECTOR          0x20
#define KEYBOARD_IRQ_VECTOR      0x21

#define SYSTEM_CALL_VECTOR       0x80

extern inline void  __enableIRQ(void){__asm__("sti"::);}
extern inline void  __disableIRQ(void){__asm__("cli"::);}

extern void timer_IRQhandler(void);
extern void keyboard_IRQhandler(void);

extern void system_call(void);
#endif
