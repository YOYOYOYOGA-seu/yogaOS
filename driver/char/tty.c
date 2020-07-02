/*
 * @Author Shi Zhangkun
 * @Date 2020-03-21 03:50:55
 * @LastEditTime 2020-06-27 02:09:05
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/driver/char/tty.c
 */
#include "tty.h"
#include "stdio.h"
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
    s_tty[i].frontColorTemp = 0xFF;
    s_tty[i].backColorTemp = 0xFF;
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
 * @note  user can use string format "/033[x;xx;xxm" to setting display color
 * @param {int} ttyNum : tty index
 * @param {char *} buf 
 * @param {int} count 
 * @retval actually number of item been writen
 */
int tty_write(int ttyNum, char *buf, int count)
{
  char *pTemp = buf;
  char colorSet[] = "/033[";
  int flagHL;
  int i;

  if(ttyNum >= SYS_TTY_NUM)
    return 0;

  for(i = 0; i < sizeof("/033[") - 1; i++)   // if there are a setting code 
  {
    if(*pTemp == *(colorSet + i))
      pTemp++;
    else
      goto copyString;
    
  }
  tty_outputData(ttyNum);   //before setting color, clear all output buf
  
  if(*pTemp =='0'&&*(pTemp+1) == 'm')   //default display color
  {
    s_tty[ttyNum].backColor = BLACK;
    s_tty[ttyNum].frontColor = WHITE;
    buf = pTemp + 2;
    goto copyString;   //setting complete
  }

  else if(*(pTemp+1) == ';')
  {
    switch (*pTemp)
    {
    case '0':
      flagHL = 0;      // defult
      break;
    case '1':
      flagHL = 1;      // high light
      break;

    default:
      goto copyString;   //error code (don't support)
      break;
    }
  }
  pTemp+=2;
  for(i = 0; i<2 ; i++)
  {
    if (*pTemp == '3')  //front color set
    {
      pTemp++;
      switch (*pTemp)
      {
      case '0':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = GRAY ): (s_tty[ttyNum].frontColorTemp = BLACK);
        break;
      case '1':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_RED) : (s_tty[ttyNum].frontColorTemp = RED);
        break;
      case '2':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_GREEN) : (s_tty[ttyNum].frontColorTemp = GREEN);
        break;
      case '3':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_BROWN) : (s_tty[ttyNum].frontColorTemp = BROWN);
        break;
      case '4':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_BLUE) : (s_tty[ttyNum].frontColorTemp = BLUE);
        break;
      case '5':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_MAGENTA) : (s_tty[ttyNum].frontColorTemp = MAGENTA);
      case '6':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_CYAN) : (s_tty[ttyNum].frontColorTemp = CYAN);
        break;
      case '7':
        (flagHL == 1) ? (s_tty[ttyNum].frontColorTemp = HL_WHITE) : (s_tty[ttyNum].frontColorTemp = WHITE);
        break;

      default:
        goto copyString; //error code (not support)
        break;
      }
      pTemp++;
    }
    else if(*pTemp == '4')
    {
      pTemp++;
      switch (*pTemp)
      {
      case '0':
        s_tty[ttyNum].backColorTemp = BLACK;
        break;
      case '1':
        s_tty[ttyNum].backColorTemp =  RED;
        break;
      case '2':
        s_tty[ttyNum].backColorTemp = GREEN;
        break;
      case '3':
        s_tty[ttyNum].backColorTemp = BROWN;
        break;
      case '4':
        s_tty[ttyNum].backColorTemp = BLUE;
        break;
      case '5':
        s_tty[ttyNum].backColorTemp = MAGENTA;
      case '6':
        s_tty[ttyNum].backColorTemp = CYAN;
        break;
      case '7':
        s_tty[ttyNum].backColorTemp = WHITE;
        break;
      default:
        goto copyString; //error code (not support)
        break;
      }
      pTemp++;
    }
    else
    {
      goto copyString;   //error  code format
    }
    
    if(*pTemp == ';' && i==0) 
    {
      pTemp++;
      continue;
    }
    else if(*pTemp == 'm')  
    {
      buf = pTemp + 1;
      goto copyString;   //complete setting
    }
    else
    {
        goto copyString;   //error  code format
    }
  }
  



copyString:
  for(i = 0; i < count; i++)
  {
    if(queue_write(*buf++,&s_tty[ttyNum].outputQueue))
      break;
  }
  return i;
}
/**
 * @brief  out put all data in outputBuf to it's tty output device
 * @note  
 * @param {int} ttyNum : tty index
 * @retval none
 */
void tty_outputData(int ttyNum)
{
  char temp[TTY_OUTPUT_BUFF_SIZE];
  int count = queue_read(TTY_OUTPUT_BUFF_SIZE,temp,&s_tty[ttyNum].outputQueue);
  if(s_tty[ttyNum].type == TTY_TYPE_STD)
  {
    if(count)
    {
      console_dispStr(temp,count,s_tty[ttyNum].consoleIndex, \
                      (s_tty[ttyNum].backColorTemp >0xf)?s_tty[ttyNum].backColor:s_tty[ttyNum].backColorTemp, \
                      (s_tty[ttyNum].frontColorTemp > 0xf)?s_tty[ttyNum].frontColor:s_tty[ttyNum].frontColorTemp);

    }
    s_tty[ttyNum].backColorTemp = 0xFF;
    s_tty[ttyNum].frontColorTemp = 0xFF;
  }
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
  uint32_t key = 0;
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
      if(scanCode == 0x2A)
      {
        uint32_t tempS[2] = {0,0};
        kb_read(2,tempS);
        if(tempS[0] == 0xE0&&tempS[1]==0x37)
        {
          key = PRINTSCREEN;
        }
      }
      else if(scanCode == 0xB7)
      {
        uint32_t tempS[2] = {0,0};
        kb_read(2,tempS);
        if(tempS[0] == 0xE0&&tempS[1]==0xAA)
        {
          key = PRINTSCREEN|FLAG_BREAK;
        }
      }
      else
        flag_E0 = 1;
    }
    if( key != PRINTSCREEN /* && key != PAUSE */)
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
        key = 0;
        break;
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
     //backspace can delete all character or backspace can only delete char send to user task(in charBuff)
      if(ptty->flag & TTY_FLAG_BS_GLOBAL ||  ptty->cbCount > 0) 
      {
        queue_write(8,&ptty->outputQueue);
      }
      if( ptty->cbCount > 0)  //
        ptty->cbCount --;    
      break;
      
    case PRINTSCREEN:
      if(ptty->type == TTY_TYPE_STD)
      {
        char temp_buf[30];
        int len;
        pCurrentActiveTTY->frontColorTemp = GREEN;
        len = sprintf(temp_buf," -This is Console: %d- ",pCurrentActiveTTY->consoleIndex);
        tty_write(pCurrentActiveTTY->ttyIndex,temp_buf,len);
      }
      else
      {
        /* stty code */
      }
      break;

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

    default:
      break;
    }
  }
  else if(key&(FLAG_ALT_L|FLAG_ALT_R))   //compound key: Alt + xxx
  {
    switch (key&((FLAG_EXT<<1)-1))
    {
    case UP:
       if(ptty->type == TTY_TYPE_STD)
        console_pageMove(ptty->consoleIndex,1,0);
      else
      {
        /* stty code */
      }
      break;
    case DOWN:
      if(ptty->type == TTY_TYPE_STD)
        console_pageMove(ptty->consoleIndex,1,1);
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