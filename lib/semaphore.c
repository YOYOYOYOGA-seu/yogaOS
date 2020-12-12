/*
 * @Author Shi Zhangkun
 * @Date 2020-11-06 23:52:53
 * @LastEditTime 2020-11-07 02:11:05
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/semaphore.c
 */
#include "semaphore.h"
/* ！！！！！ 当前yogaOS不支持多线程，所以没有实现的必要 */
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value)
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
extern int sem_destroy (sem_t *__sem)
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
extern int sem_wait (sem_t *__sem)
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
extern int sem_trywait (sem_t *__sem) 
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
extern int sem_post (sem_t *__sem) 
{
  return 0;
}

/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
extern int sem_getvalue (sem_t *__restrict __sem, int *__restrict __sval)
{
  return 0;
}