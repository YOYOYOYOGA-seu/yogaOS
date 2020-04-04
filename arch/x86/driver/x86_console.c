/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 20:36:31
 * @LastEditTime 2020-04-04 04:55:18
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/driver/x86_console.c
 */
#include "console.h"
#include "vga.h"
#include "io.h"
#include "address.h"
/* ------------------------------------- define --------------------------------------- */
#define CONSOLE_HIGHT           25
#define CONSOLE_WIDTH           80
#define UNIT_SIZE               2

#define CONSOLE_LINE_SIZE       (CONSOLE_WIDTH*UNIT_SIZE)
#define CONSOLE_SCREEN_SIZE     (CONSOLE_HIGHT*CONSOLE_WIDTH*UNIT_SIZE)
#define TOTAL_VEDIO_MEM_SIZE    0x8000   //32KB
#define CONSOLE_MAX_MEM_SIZE    0x2800    //10KB

/* ------------------------------------- variables --------------------------------------- */
static console_t s_console[SYS_MAX_CONSOLE_NUM];
static uint32_t numOfConsoleUsed = 0;
extern uint32_t disp_pos;

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void console_init(void)
{
  int i;
  for(i = 0; i < SYS_MAX_CONSOLE_NUM; i++)
  {
    s_console[i].baseAddr = CONSOLE_MAX_MEM_SIZE * i;  // segment VEDIO base addr = VIDEO_MEM_BASE_ADDR
    s_console[i].cursor = 0;
    s_console[i].limit = CONSOLE_MAX_MEM_SIZE;
    s_console[i].unitSize = UNIT_SIZE;
    s_console[i].currentStartAddr = s_console[i].baseAddr;
    s_console[i].lastLFline = -1;
    s_console[i].Usingflag = 0;

  }
  s_console[0].cursor = disp_pos;    // number 0 console's cursor linked to the disp_pos before tty is inited

}

/**
 * @brief  alloc one console to link to a tty struct
 * @note  
 * @param {type} none
 * @retval index of console
 */
uint32_t console_alloc(void)
{
  if(numOfConsoleUsed >= SYS_MAX_CONSOLE_NUM)
    return SYS_MAX_CONSOLE_NUM + 1;
  for(int i = 0; i < CONSOLE_MAX_MEM_SIZE; i++)
  {
    if(!s_console[i].Usingflag)
    {
      s_console[i].Usingflag = 1;
      numOfConsoleUsed ++;
      return i;
    }
  }
  return SYS_MAX_CONSOLE_NUM + 1;
}
/**
 * @brief  
 * @note  
 * @param {uint32_t} local : location of cursor, relative address from base addr of video memory(.baseAddr + .cursor)
 * @retval none
 */ 
void vga_setCursor(uint32_t local)
{
  __disableIRQ();
  IO_outByte((uint8_t)VGA_CURSOR_H,(uint16_t)VGA_CRT_ADDR);
  IO_outByte((uint8_t)((local/2)>>8 & 0xff),(uint16_t)VGA_CRT_DATA);
  IO_outByte((uint8_t)VGA_CURSOR_L,(uint16_t)VGA_CRT_ADDR);
  IO_outByte((uint8_t)((local/2) & 0xff),(uint16_t)VGA_CRT_DATA);
  __enableIRQ();
}

/**
 * @brief  switch screen to a console
 * @note  
 * @param {uint32_t} consoleNum : console index
 * @retval none
 */
void console_switch(uint32_t consoleNum)
{
  __disableIRQ();
  IO_outByte(VGA_START_ADDR_H,VGA_CRT_ADDR);
  IO_outByte(((s_console[consoleNum].currentStartAddr/2)>>8)&0xff,VGA_CRT_DATA);
  IO_outByte(VGA_START_ADDR_L,VGA_CRT_ADDR);
  IO_outByte((s_console[consoleNum].currentStartAddr/2)&0xff,VGA_CRT_DATA);
  __enableIRQ();
 vga_setCursor(s_console[consoleNum].cursor + s_console[consoleNum].baseAddr);

}

/**
 * @brief  move page up or down for appoint lines
 * @note  
 * @param {uint32_t} consoleNum
 * @param {uint32_t} line : lines want to move
 * @param {uint32_t} dir : 1  page down 0  page up 2  relocate to cursor               
 * @retval none
 */
void console_pageMove(uint32_t consoleNum, uint32_t line, uint32_t dir)
{
  uint32_t cursorline;
  cursorline =  s_console[consoleNum].cursor - s_console[consoleNum].cursor % CONSOLE_LINE_SIZE;
  if(dir == 1) //page down
  {
    if(s_console[consoleNum].currentStartAddr + CONSOLE_SCREEN_SIZE > s_console[consoleNum].baseAddr + s_console[consoleNum].cursor)
      return;
    s_console[consoleNum].currentStartAddr += line * CONSOLE_LINE_SIZE;
    if(s_console[consoleNum].currentStartAddr + CONSOLE_SCREEN_SIZE > cursorline + CONSOLE_LINE_SIZE + s_console[consoleNum].baseAddr)  //page start line can't higher than cusor line
    {
      s_console[consoleNum].currentStartAddr =s_console[consoleNum].baseAddr + cursorline + CONSOLE_LINE_SIZE - CONSOLE_SCREEN_SIZE;
    }
    // if reached consor mem button
    if(s_console[consoleNum].currentStartAddr + CONSOLE_SCREEN_SIZE > s_console[consoleNum].baseAddr + s_console[consoleNum].limit)
    {
      s_console[consoleNum].currentStartAddr = s_console[consoleNum].baseAddr + s_console[consoleNum].limit - CONSOLE_SCREEN_SIZE;
    }
  }
  else if(dir == 0) // page up
  {
    if(s_console[consoleNum].currentStartAddr > s_console[consoleNum].baseAddr + line * CONSOLE_LINE_SIZE)
      s_console[consoleNum].currentStartAddr -= line * CONSOLE_LINE_SIZE;
    else 
      s_console[consoleNum].currentStartAddr = s_console[consoleNum].baseAddr;
    /* code */
  }
  else if(dir == 2) // relocate to cursor
  {
    if(s_console[consoleNum].baseAddr + cursorline + CONSOLE_LINE_SIZE > CONSOLE_SCREEN_SIZE)
      s_console[consoleNum].currentStartAddr =s_console[consoleNum].baseAddr + cursorline + CONSOLE_LINE_SIZE - CONSOLE_SCREEN_SIZE;
    else
      s_console[consoleNum].currentStartAddr = s_console[consoleNum].baseAddr;
  }
  
  __disableIRQ();
  IO_outByte(VGA_START_ADDR_H,VGA_CRT_ADDR);
  IO_outByte(((s_console[consoleNum].currentStartAddr/2)>>8)&0xff,VGA_CRT_DATA);
  IO_outByte(VGA_START_ADDR_L,VGA_CRT_ADDR);
  IO_outByte((s_console[consoleNum].currentStartAddr/2)&0xff,VGA_CRT_DATA);
  __enableIRQ();
}

void console_moveToCusor(uint32_t consoleNum)
{

}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void console_blockShift(uint32_t consoleNum)
{

}

/**
 * @brief  
 * @note  
 * @param {uint16_t} temp : high 8 bit respect color(back,front), low 8 bit is char data
 * @param {uint32_t} addr
 * @retval none
 */
inline void console_writeMem(uint16_t temp,uint32_t addr)
{
      __asm__("mov %0, %%gs:(%1)"
              :
              :"r"(temp),"d"(addr)
              );
}

/**
 * @brief  display string to a console from a output buff
 * @note   write char buff to console's part of video memory
 * @param {char *} pstr : base addr of output char buff
 * @param {uint32_t} num : numbers of output char
 * @param {uint32_t} consoleNum : console index
 * @param {uint8_t}  bColor : back color 
 * @param {uint8_t}  fColor : front color 
 * @retval none
 */
uint32_t console_dispStr(char *pstr, uint32_t num, uint32_t consoleNum, uint8_t bColor, uint8_t fColor)
{
  int i;
  uint32_t addr;
  uint16_t temp = (bColor&0xF)<<12|(fColor&0xF)<<8;
  if(consoleNum >= SYS_MAX_CONSOLE_NUM)
    return 0;   //注意！！！！！后期改为printk提示
  for(i = 0; i < num; i++)
  {
    if(pstr[i] == '\n') // line feed
    {
      s_console[consoleNum].lastLFline = s_console[consoleNum].cursor/CONSOLE_LINE_SIZE; //record newest LF line
      s_console[consoleNum].cursor += UNIT_SIZE * CONSOLE_WIDTH;
    }

    else if (pstr[i] == '\r') // return to the beginning of line
    {
      s_console[consoleNum].cursor -= s_console[consoleNum].cursor%(UNIT_SIZE * CONSOLE_WIDTH);
    }

    else if(pstr[i] == 8) //backspace
    {
      //if backspace to the begining of one line, and last line end with LF flag, then can't continue backspace to last line
      if(!(s_console[consoleNum].cursor % CONSOLE_LINE_SIZE)&&    \
            s_console[consoleNum].cursor/CONSOLE_LINE_SIZE <= s_console[consoleNum].lastLFline + 1)
      {
        continue;   
      }
      s_console[consoleNum].cursor -= UNIT_SIZE;
      addr = s_console[consoleNum].baseAddr + s_console[consoleNum].cursor;
      temp = (temp&0xff00) + ' ';
      console_writeMem(temp,addr);  // write ' ' to erase
    }

    if(s_console[consoleNum].cursor > s_console[consoleNum].limit )  // reach the top of this console memory
    {
      console_blockShift(consoleNum);  // shift all console memory to get some free memory
    }
    if(s_console[consoleNum].cursor > s_console[consoleNum].currentStartAddr + CONSOLE_SCREEN_SIZE -s_console[consoleNum].baseAddr) // out of the screen
    {
      console_pageMove(consoleNum,1,2); //page down 1 line
    }
    if(pstr[i] >= 32)  // Ensure only printable ascii can be print(like '\r','\n')
    {
      addr = s_console[consoleNum].baseAddr + s_console[consoleNum].cursor;
      temp = (temp&0xff00) + pstr[i];
      console_writeMem(temp,addr);
      s_console[consoleNum].cursor += UNIT_SIZE;
    }
    
  }
  vga_setCursor(s_console[consoleNum].cursor + s_console[consoleNum].baseAddr);
  return 0;
}