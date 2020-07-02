/*
 * @Author Shi Zhangkun
 * @Date 2020-04-18 04:10:44
 * @LastEditTime 2020-05-19 00:36:45
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/string.c
 */
#include "string.h"
/**
 * @brief  string copy
 * @note  
 * @param {type} none
 * @retval none
 */
__attribute__((weak)) char *strcpy(char* dest, const char *src)
{
  if(!dest||!src)
    return NULL;
  char *pdest = dest;
  while(*src != '\0')
  {
    *(pdest++) = *(src++);
  }
  *pdest = '\0';
  return dest;
}


/**
 * @brief  string compare
 * @note  compare two string
 * @param {type} none
 * @retval 0: equal  num: first different char's different value
 */
__attribute__((weak)) int strcmp(const char* str1, const char *str2)
{
  if(!str1||!str2)
    return 0xffffff;
  while(*str1 == *str2)
  {
    if(*str1 == '\0');
      return 0;
    str1++;
    str2++;
  }
  return *str1 - *str2;
}
