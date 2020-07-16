/*
 * @Author Shi Zhangkun
 * @Date 2020-03-27 02:00:42
 * @LastEditTime 2020-04-18 02:07:57
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/driver/console.h
 */
#ifndef __CONSOLE_H
#define __CONSOLE_H
#include "yogaOS/types.h"

typedef struct{
  uint32_t currentStartAddr; /* current screen start base of this console in video mem */
  uint32_t baseAddr;     /* base addr of this console's video mem */
  uint32_t limit;            
  uint32_t unitSize;         /* one char occupies memsize in video mem */
  uint32_t cursor;           /* cursor location in this console (relative location of base addr)*/
  int lastLFline;       /* last LF flag location, use for erase(backspace) handler, can't erase char before LF code */
  uint32_t Usingflag;       /* if linked to a tty struct */
}console_t;

/* ---------------------console color ,4 bit RGB (high_light:R:G:B)---------------------- */
#define BLACK         0x0
#define BLUE          0x1
#define GREEN         0x2
#define CYAN          0x3
#define RED           0x4
#define MAGENTA       0x5
#define BROWN         0x6
#define WHITE         0x7

#define GRAY          0x8
#define HL_BLUE       0x9
#define HL_GREEN      0xa
#define HL_CYAN       0xb
#define HL_RED        0xc
#define HL_MAGENTA    0xd
#define HL_BROWN      0xe
#define HL_WHITE      0xf
/* ------------------------------------- define --------------------------------- */
#define CONSOLE_PAGE_UP     0
#define CONSOLE_PAGE_DOWN   1
/* --------------------------------- function prototype ------------------------- */
void console_switch(uint32_t consoleNum);
void console_pageMove(uint32_t consoleNum, uint32_t line, uint32_t dir);
void console_blockShift(uint32_t consoleNum);
uint32_t console_dispStr(char *pstr, uint32_t num, uint32_t consoleNum, uint8_t bColor, uint8_t fColor);
void console_init(void);
uint32_t console_alloc(void);
#define SYS_MAX_CONSOLE_NUM 3
#endif