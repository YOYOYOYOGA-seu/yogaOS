/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:38:31
 * @LastEditTime 2020-04-04 02:11:50
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/vsprintf.c
 */
#include "stdarg.h"
#include "stdlib.h"
#include "string.h"

/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
int vsprintf(char *string, char *format, va_list param)
{
  char * pChar;
  va_list tempParam = param;
  //char temp_buf[256];

  for(pChar = string; *format; format ++)  
  {
    if(*format != '%') //if const char
    {
      *pChar++ = *format;
      continue; 
    }

    format++;
    switch (*format)
    {
    case 'x':
      itoa(*((int*)tempParam),pChar,16);
      while(*pChar)
        pChar++;
      tempParam += 4;
      break;

    case 'd':
      itoa(*((int*)tempParam),pChar,10);
      while(*pChar)
        pChar++;
      tempParam += 4;
      break;
    
    case 'f':
      break;
    
    case 's':
      break;
    default:
      break;
    }
    
  }
  *pChar = '\0';
  return (pChar - string);
}