/*
 * @Author Shi Zhangkun
 * @Date 2020-03-21 03:50:55
 * @LastEditTime 2020-04-04 07:19:34
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/driver/char/tty.c
 */
#include "tty.h"

uint32_t keyState;
tty_t s_tty[SYS_TTY_NUM];
tty_t * pCurrentActiveTTY = NULL;

/**
 * @brief  init tty driver and data struct
 * @note  
 * @param {type} none
 * @retval none
 */
void tty_init(void)
{
  int i;
  console_init();
  kb_init();
  for(i = 0;i<SYS_TTY_NUM;i++)
  {
    //queue_init(TTY_CHAR_BUFF_SIZE,sizeof(char),s_tty[i].charBuff,&s_tty[i].charQueue);
    queue_init(TTY_OUTPUT_BUFF_SIZE,sizeof(char),s_tty[i].outputBuff,&s_tty[i].outputQueue);
    s_tty[i].cbCount = 0;
    s_tty[i].type = TTY_TYPE_STD;  // standard tty 

    s_tty[i].consoleIndex = console_alloc();
    s_tty[i].ttyIndex = i;

    s_tty[i].readTask = 0;
    s_tty[i].readNum = 0;
    s_tty[i].operateFlag = 0;

    s_tty[i].flag = TTY_FLAG_ECHO|TTY_FLAG_NLCR|TTY_FLAG_BS_GLOBAL;
  
    
    s_tty[i].frontColor = WHITE;
    s_tty[i].backColor = BLACK;
  }
  pCurrentActiveTTY = s_tty;
}

/**
 * @brief  transfer capital between lowercase
 * @note  
 * @param {char} c 
 * @retval transferred char
 */
char ascii_CapsTransfer(char c)
{
  if(c <= 90 && c >= 65) //capital
    return c + 32;
  else if(c <= 122 && c >= 97)
    return c - 32;
  else
    return c;
  
}
/**
 * @brief  write char to tty out put
 * @note  
 * @param {int} ttyNum : tty index
 * @param {char *} buf 
 * @param {int} count 
 * @retval actually number of item been writen
 */
int tty_write(int ttyNum, char *buf, int count)
{
  int i;
  if(ttyNum >= SYS_TTY_NUM)
    return 0;
  for(i = 0; i < count; i++)
  {
    if(queue_write(*buf++,&s_tty[ttyNum].outputQueue))
      break;
  }
  return i;
}
/**
 * @brief  switch current active tty
 * @note  
 * @param {tty_t *} ptty
 * @retval error_t
 */
error_t tty_switchTTY(tty_t *ptty)
{
  pCurrentActiveTTY = ptty;
  if(pCurrentActiveTTY->type == TTY_TYPE_STD)
    console_switch(ptty->consoleIndex);
  else
  {
    /* code */
  }
  
  
}
/**
 * @brief  decode the scancode from input device
 * @note   key code strcute : 
 *        |    bit0 - bit7   |          bit8        |    bit9 - bit 31     |
 *        |       data       |    flag extern key   |  flag of ctrl,alt... |
 * @param {tty_t *} ptty 
 * @retval uint32_t :key code 
 */
uint32_t tty_decode(tty_t * ptty)
{
  uint32_t scanCode = 0;
  uint32_t count = 0;
  uint32_t flag_E0 = 0;
  uint32_t make = 0;
  uint32_t column = 0;
  uint32_t key;
  if(ptty->type == TTY_TYPE_STD)  // a standard tty, input from keyboard
  {
    count = kb_read(1,&scanCode);
    if(!count)
      return 0;
    if(scanCode == 0xE1)   //PAUSE key(don't support yet)
    {

    }
    else if(scanCode == 0xE0)// PrintScreen(don't support yet) or other(F1, F2,ESC....)
    {
      if(!kb_read(1,&scanCode))
        return 0;                 /* incomplete  scancode  */
      
      flag_E0 = 1;
    }
    if(1/* key != PRINTSCREEN && key != PAUSE */)
    {
      make = (scanCode & FLAG_BREAK ? 0:1);

      column = 0;
      if(keyState&FLAG_SHIFT_L || keyState&FLAG_SHIFT_R)
        column = 1;
      if(flag_E0)
      {
        column = 2;     
        flag_E0 = 0;
      }
      key =  keymap[(scanCode&0x7F) * MAP_COLS + column];                                      // make code
      switch (key)
      {
      case SHIFT_L:
        make ? (keyState |= FLAG_SHIFT_L ): (keyState &= ~FLAG_SHIFT_L);
        key = 0;
        break;
      case SHIFT_R:
        make ? (keyState |= FLAG_SHIFT_R) : (keyState &= ~FLAG_SHIFT_R);
        key = 0;
        break;
      case ALT_L:
        make ? (keyState |= FLAG_ALT_L) : (keyState &= ~FLAG_ALT_L);
        key = 0;
        break;
      case ALT_R:
        make ? (keyState |= FLAG_ALT_R) : (keyState &= ~FLAG_ALT_R);
        key = 0;
        break;
      case CTRL_L:
        make ? (keyState |= FLAG_CTRL_L) : (keyState &= ~FLAG_CTRL_L);
        key = 0;
        break;
      case CTRL_R:
        make ? (keyState |= FLAG_CTRL_R) : (keyState &= ~FLAG_CTRL_R);
      case CAPS_LOCK:
        if(make)
          {
            if(keyState&FLAG_CAPS)
              keyState &= ~(FLAG_CAPS);
            else
              keyState |= FLAG_CAPS;
          }
        key = 0;
        break;

      default:     //if notbreak code
        if(!make)
          key = 0;
        break;
      }
      
    }
  }
  else 
  {
    /* serial tty */
  }
  if(key)
    return key + (keyState&(~(FLAG_EXT - 1)));
  else
    return 0;
  
}

/**
 * @brief  tty handler function, handler different key code
 * @note  key code strcute : 
 *        |    bit0 - bit7   |          bit8        |    bit9 - bit 31     |
 *        |       data       |    flag extern key   |  flag of ctrl,alt... |
 * 
 * @param {uint32_t} key :key code 
 *        {tty_t *} tty 
 * @retval none
 */
void tty_process(uint32_t key,tty_t * ptty)
{
  if(key == 0)
    return;
  char ascii;  //tasfer key to ascii
  
  if(!(key & (FLAG_EXT|FLAG_CTRL_L|FLAG_CTRL_R|FLAG_ALT_L|FLAG_ALT_R)))  //single printable key 
  {
    ascii = (char)(key&0xff);
    if(key & FLAG_CAPS)
      ascii = ascii_CapsTransfer(ascii);
    if(ptty->operateFlag == TTY_OP_TASK_READING) //if need write charBuff for task reading
    {
      if(ptty->cbCount >= ptty->readNum ||ptty->cbCount >= TTY_CHAR_BUFF_SIZE) //if compelet
      {
        //注意！！！！！这里填上唤醒等待读取的任务
      }
      else
      {
        ptty->charBuff[ptty->cbCount] = ascii;
        ptty->cbCount ++;
      }
    }
    if(ptty->flag & TTY_FLAG_ECHO)  //if open echo
    {
      queue_write(ascii,&ptty->outputQueue);
    }
  }
  else if((key&FLAG_EXT)&&!(key & (FLAG_CTRL_L|FLAG_CTRL_R|FLAG_ALT_L|FLAG_ALT_R))) //single function keys
  {
    switch (key&((FLAG_EXT<<1)-1))
    {
    case ENTER:
      if((ptty->flag & TTY_FLAG_NLCR) && (ptty->flag & TTY_FLAG_ECHO))  //if open echo
      {
        queue_write('\n',&ptty->outputQueue);
        queue_write('\r',&ptty->outputQueue);
      }
      if(ptty->operateFlag == TTY_OP_TASK_READING) //if some task is reading, then finish it(enter key)
      {
        //注意！！！！！这里填上唤醒等待读取的任务
      }
      break;
      
    case BACKSPACE:
     //backspace can delete all character or backspace can only delete char sent to user task(in charBuff)
      if(ptty->flag & TTY_FLAG_BS_GLOBAL ||  ptty->cbCount > 0) 
      {
        queue_write(8,&ptty->outputQueue);
      }
      if( ptty->cbCount > 0)  //
        ptty->cbCount --;    
      break;

    default:
      break;
    }
  }
  else if(key&(FLAG_ALT_L|FLAG_ALT_R))   //compound key: Alt + xxx
  {
    switch (key&((FLAG_EXT<<1)-1))
    {
    case PAGEUP:
       if(ptty->type == TTY_TYPE_STD)
        console_pageMove(ptty->consoleIndex,10,0);
      else
      {
        /* stty code */
      }
      break;
    case PAGEDOWN:
      if(ptty->type == TTY_TYPE_STD)
        console_pageMove(ptty->consoleIndex,10,1);
      else
      {
        /* stty code */
      }
      break;
    case F1:
      tty_switchTTY(&s_tty[0]);
      break;
    case F2:
      tty_switchTTY(&s_tty[1]);      
      break;
    case F3:
      tty_switchTTY(&s_tty[2]);
      break;
    default:
      break;
    }
    
  }


}