/*
 * @Author Shi Zhangkun
 * @Date 2020-12-30 22:37:18
 * @LastEditTime 2020-12-30 22:43:51
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/upanic.c
 */
#include "yogaOS/upanic.h"
#include "yogaOS/types.h"

extern int enterSystemCall(int vector,int arg_1, int arg_2, int arg_3);
void upanic(const char * str)
{
  enterSystemCall(SYS_PANIC_VECTOR,(int)str,0,0);
}

