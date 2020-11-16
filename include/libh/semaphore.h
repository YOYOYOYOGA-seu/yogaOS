/*
 * @Author Shi Zhangkun
 * @Date 2020-11-01 07:03:05
 * @LastEditTime 2020-11-01 07:56:50
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/semaphore.h
 */
#ifndef __SEMAPHORE_H
#define __SEMAPHORE_H

#include <yogaOS/types.h>


#define __SIZEOF_SEM_T	16

/* In this vision not support named semaphore (can,t shared between proccess) */
typedef union
{
  char __size[__SIZEOF_SEM_T];
  long int __align;
} sem_t;


/* Initialize semaphore object SEM to VALUE.  If PSHARED then share it
   with other processes.  */
extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value);
/* Free resources associated with semaphore object SEM.  */
extern int sem_destroy (sem_t *__sem);
/* Wait for SEM being posted.*/
extern int sem_wait (sem_t *__sem);
/* Test whether SEM is posted.  */
extern int sem_trywait (sem_t *__sem) ;
/* Post SEM.  */
extern int sem_post (sem_t *__sem) ;
/* Get current value of SEM and store it in *SVAL.  */
extern int sem_getvalue (sem_t *__restrict __sem, int *__restrict __sval);



#endif	/* semaphore.h */
