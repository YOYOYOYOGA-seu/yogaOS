/*
 * @Author Shi Zhangkun
 * @Date 2020-02-29 04:35:35
 * @LastEditTime 2020-11-13 04:02:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/irq.h
 */
#ifndef __IRQ_H
#define __IRQ_H

#include "yogaOS/types.h"

#define DEVIDE_ERROR             0x00
#define PAGE_FAULT               0x0E
/* external interrupt (controller 8259A) */
#define TIMER_IRQ_VECTOR          0x20
#define KEYBOARD_IRQ_VECTOR      0x21
#define EXTERN_IRQ_OTHER_USE     0x22     //connect to 8259A slave chip 
#define SERIAL_1_IRQ_VECTOR      0x23
#define SERIAL_2_IRQ_VECTOR      0x24
#define LPT2_IRQ_VECTOR          0x25
#define FLOPPY_IRQ_VECTOR        0x26
#define LPT1_IRQ_VECTOR          0x27
#define RTC_IRQ_VECTOR           0x28
#define EXTERN_IRQ_EMPTY_2       0x29
#define EXTERN_IRQ_EMPTY_3       0x2A
#define EXTERN_IRQ_EMPTY_4       0x2B
#define MOUSE_IRQ_VECTOR         0x2C
#define FPU_IRQ_VECTOR           0x2D
#define HD_IRQ_VECTOR            0x2E
#define EXTERN_IRQ_EMPTY_5       0x2F
/* systemcall */
#define SYSTEM_CALL_VECTOR       0x80

#define EXTERN_IRQ_START         TIMER_IRQ_VECTOR
#define EXTERN_IRQ_END           EXTERN_IRQ_EMPTY_5
#define MAX_IRQ_NUMBER           0xFF

void irq_enableExt(int irq);
void irq_disableExt(int irq);
error_t irq_registerExtHandler(int irq_ext,void (*handler)(void));

#endif
