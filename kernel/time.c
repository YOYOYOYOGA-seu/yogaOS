/*
 * @Author Shi Zhangkun
 * @Date 2020-02-29 01:51:17
 * @LastEditTime 2020-10-31 08:35:13
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/kernel/time.c
 */

unsigned int timeCount = 0;

unsigned int time_getTimeCount(void)
{
  return timeCount;
}