/*
 * @Author Shi Zhangkun
 * @Date 2022-04-14 15:20:33
 * @LastEditTime 2022-04-14 15:22:29
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /yogaOS/include/libh/stddef.h
 */
#ifndef __STDDEF_H
#define __STDDEF_H

#define offsetof(TYPE, MEMBER)  ((size_t) &((TYPE *)0)->MEMBER)

#endif