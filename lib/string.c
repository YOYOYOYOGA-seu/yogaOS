/*
 * @Author Shi Zhangkun
 * @Date 2020-04-18 04:10:44
 * @LastEditTime 2022-04-18 16:18:10
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/lib/string.c
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

/**
 * @brief  gernal memory area compare
 * @note  compare two memory area
 * @param {type} none
 * @retval 0: equal  num: first different char's different value
 */
__attribute__((weak))int memcmp(const void *str1, const void *str2, size_t n)
{
  if(!str1||!str2)
    return 0xffffff;
  for(size_t i = 0; i < n; i++)
  {
    if(((const char*)str1)[i] != ((const char*)str2)[i])
      return ((const char*)str1)[i] - ((const char*)str2)[i];
  }
  return 0;
}

/**
 * @brief  gernal memory area compare
 * @note  compare two memory area
 * @param {type} none
 * @retval 0: equal  num: first different char's different value
 */
__attribute__((weak))size_t strlen(const char *str)
{
  if (!str) return 0;
  int len = 0;
  while (*str++ != '\0')
    len++;
  return len;
}
