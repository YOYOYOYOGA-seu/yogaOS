/*
 * @Author Shi Zhangkun
 * @Date 2020-02-25 02:47:31
 * @LastEditTime 2020-04-18 04:10:38
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/lib/string_x86.c
 */
#include "string.h"
/**
 * @brief  memory copy
 * @note  
 * @param {void *} dest :       point to the destination
 *        {const void *} src :  point to the soruce
 *        {int} n :             number
 * @retval none
 */
void * memcpy(void * dest, const void *src, int n)
{
__asm__("cld\n\t"
        "rep\n\t"
        "movsb"
        :
        :"c"(n),"S"(src),"D"(dest)
        );
  return dest;
}
/**
 * @brief  set memory
 * @note  
 * @param {type} none
 * @retval none
 */
void * memset(void *s, int ch, ssize_t n)
{
  __asm__("cld\n\t"
        "rep\n\t"
        "stosb"
        :
        :"c"(n),"a"(ch),"D"(s)
        );
}

