/*
 * @Author Shi Zhangkun
 * @Date 2020-03-07 22:02:50
 * @LastEditTime 2020-04-04 05:57:29
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/sys.h
 */
#ifndef __SYS_H
#define __SYS_H
/* ------------------------------------- prototype of system call handler func --------------------------------------- */

extern int sys_exit();             //0
extern int sys_fork();             //1
extern int sys_sleep();            //2
extern int sys_wait();             //3
extern int sys_kill();             //4
extern int sys_excve();            //5
extern int sys_getPID();           //6
extern int sys_getTime();          //7

extern int sys_write();            //8
extern int sys_read();             //9
extern int sys_open();             //10

/* *****you must correspond system call number in header file include/libh/type.h !!!***** */

/* ------------------------------------- system call handler func vector --------------------------------------- */
void * sys_call_table[]={sys_exit,sys_fork,sys_sleep,sys_wait,sys_kill,sys_excve,sys_getPID, sys_getTime,sys_write,sys_read,sys_open};
int numOfSystemCalls = sizeof(sys_call_table)/sizeof(void *);
#endif