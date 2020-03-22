/*
 * @Author Shi Zhangkun
 * @Date 2020-03-21 03:55:43
 * @LastEditTime 2020-03-21 22:10:24
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/driver/char/keyboard.c
 */
#include "keyboard.h"
static KBbuff_t keyBoardBuff;
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void kb_init(void)
{
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
    *buff = keyBoardBuff.buff[keyBoardBuff.tail];
    if(keyBoardBuff.tail < KB_BUFF_SIZE - 1)       //if reach the top addr of buff
      keyBoardBuff.tail ++;
    else
     keyBoardBuff.tail = 0;

    keyBoardBuff.count --;
    count ++;
  }
  return count;
}