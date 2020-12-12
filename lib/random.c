/*
 * @Author Shi Zhangkun
 * @Date 2020-09-12 06:16:25
 * @LastEditTime 2020-09-12 06:33:24
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/random.c
 */
#include "stdlib.h"

static unsigned long next = 1;
#define RAND_MAX 0x8000
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
int rand(void) 
{
    next = next * 1103515245 + 12345;
    return((unsigned)(next/65536) % RAND_MAX);
}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
void srand(unsigned int seed) 
{
  next = seed;
}