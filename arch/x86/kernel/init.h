/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 09:17:01
 * @LastEditTime 2020-03-08 00:41:09
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/init.h
 */
#ifndef __INIT_H
#define __INIT_H
#include "errno.h"
#include "yogaOS/types.h"

#define TIMER_FREQ   1193182

error_t initSegment(void);
void initSysMsg(void);
void initMemManage(void);
void init8254Timer(void);
#endif