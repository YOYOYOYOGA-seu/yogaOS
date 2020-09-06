/*
 * @Author Shi Zhangkun
 * @Date 2020-02-29 04:35:35
 * @LastEditTime 2020-09-05 19:44:00
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/irq.h
 */
#ifndef __IRQ_H
#define __IRQ_H
#define DEVIDE_ERROR             0x00
#define PAGE_FAULT               0x0E
#define TIME_IRQ_VECTOR          0x20
#define KEYBOARD_IRQ_VECTOR      0x21

#define SYSTEM_CALL_VECTOR       0x80


extern void page_fault(void);
extern void timer_IRQhandler(void);
extern void keyboard_IRQhandler(void);

extern void system_call(void);
#endif
