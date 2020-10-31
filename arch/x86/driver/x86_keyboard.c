/*
 * @Author Shi Zhangkun
 * @Date 2020-03-21 03:55:43
 * @LastEditTime 2020-10-31 05:51:52
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/driver/x86_keyboard.c
 */
#include "keyboard.h"
#include "irq.h"
#include "io.h"
static KBbuff_t keyBoardBuff;

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void kb_IRQHandler(void)
{
  uint8_t data;
  data = IO_inByte(IO_KB_WR_BUF);
  kb_writeBuff(data);
  if(data != 0xE0 && data != 0xE1)
  {
    //semctl();           /*注意！！！！！当后期加入IPC后，在这里发送信号量以唤醒tty服务进程
  }
  //disp_string32(key);
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void kb_init(void)
{
  irq_registerExtHandler(KEYBOARD_IRQ_VECTOR, kb_IRQHandler);
  irq_enableExt(KEYBOARD_IRQ_VECTOR);
  keyBoardBuff.head = 0;
  keyBoardBuff.tail = 0;
  keyBoardBuff.count = 0;
}

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void kb_process(void)
{
  
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void kb_writeBuff(uint8_t data)
{
  
  if(keyBoardBuff.count < KB_BUFF_SIZE)
  {
    keyBoardBuff.buff[keyBoardBuff.head] = data;   //write buff

    if(keyBoardBuff.head < KB_BUFF_SIZE - 1)       //if reach the top addr of buff
      keyBoardBuff.head ++;
    else
      keyBoardBuff.head = 0;

    keyBoardBuff.count ++;
  }
}


/**
 * @brief  
 * @note  
 * @param {uint32_t} num :number want to read
 *        {uint32_t*} buff :point to the receive buff
 * @retval number readed actually
 */
uint32_t kb_read(uint32_t num, uint32_t *buff)
{
  uint32_t count = 0;
  while(keyBoardBuff.count > 0 && count < num)
  {
    buff[count] = keyBoardBuff.buff[keyBoardBuff.tail];
    if(keyBoardBuff.tail < KB_BUFF_SIZE - 1)       //if reach the top addr of buff
      keyBoardBuff.tail ++;
    else
     keyBoardBuff.tail = 0;

    keyBoardBuff.count --;
    count ++;
  }
  return count;
}


