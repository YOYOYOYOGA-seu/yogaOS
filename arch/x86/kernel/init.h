/*
 * @Author Shi Zhangkun
 * @Date 2020-02-22 09:17:01
 * @LastEditTime 2020-10-31 06:19:54
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/kernel/init.h
 */
#ifndef __INIT_H
#define __INIT_H
#include "errno.h"
#include "yogaOS/types.h"

error_t initSegment(void);
void initSysMsg(void);
void initMemManage(void);
void initIRQ(void);
extern void init8254Timer(void);

#endif