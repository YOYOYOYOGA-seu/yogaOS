/*
 * @Author Shi Zhangkun
 * @Date 2020-10-31 05:46:39
 * @LastEditTime 2020-10-31 06:19:39
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/driver/timer8254.c
 */
#include "irq.h"
#include "io.h"
#include "time.h"
#include "sched.h"
#include "yogaOS/types.h"

#define TIMER_FREQ   1193182
extern long timeCount;

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void timer8254_IRQHandler(void)
{
  timeCount+= SYSTEM_TICK;
  /*  test code
  if(timeCount%1000 == 0)
    disp_string32("a\0");
    */
  sched_timeTick();
}


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */

void init8254Timer(void)
{
  irq_registerExtHandler(TIMER_IRQ_VECTOR,timer8254_IRQHandler);
  irq_enableExt(TIMER_IRQ_VECTOR); //kernel use extern timer irq as it's beats 
  IO_outByte(0x34,0x43);
  IO_outByte((uint8_t)TIMER_FREQ*SYSTEM_TICK/1000,0x40);
  IO_outByte((uint8_t)((TIMER_FREQ*SYSTEM_TICK/1000)>>8),0x40);
  
}