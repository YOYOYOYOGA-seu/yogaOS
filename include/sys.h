/*
 * @Author Shi Zhangkun
 * @Date 2020-03-07 22:02:50
 * @LastEditTime 2022-04-18 15:53:17
 * @LastEditors Shi Zhangkun
 * @Description warnning!! this file can only be included once!!!
 * @FilePath /yogaOS/include/sys.h
 */
#ifndef __SYS_H
#define __SYS_H

/* ------------------------------------- prototype of system call handler func --------------------------------------- */
extern int sys_request();   //0
extern int sys_exit();    
extern int sys_fork();             
extern int sys_sleep();           
extern int sys_wait();            
extern int sys_kill();          //5
extern int sys_excve();            
extern int sys_getPID();           
extern int sys_getTime();         

extern int sys_write();        //9
extern int sys_read();             
extern int sys_open();  

extern int sys_malloc();
extern int sys_free();
extern int sys_serv();
extern int sys_panic();
/* *****you must correspond system call number in header file include/libh/yogaOS/types.h !!!***** */

/* ------------------------------------- system call handler func vector --------------------------------------- */
void * sys_call_table[]={sys_request,sys_exit,sys_fork,sys_sleep,sys_wait,sys_kill, \
                        sys_excve,sys_getPID, sys_getTime,sys_write,sys_read,sys_open, \
                        sys_malloc,sys_free,sys_serv,sys_panic};
int numOfSystemCalls = sizeof(sys_call_table)/sizeof(void *);
#endif