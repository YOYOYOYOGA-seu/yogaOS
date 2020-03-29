/*
 * @Author Shi Zhangkun
 * @Date 2020-03-26 21:36:16
 * @LastEditTime 2020-03-27 01:00:50
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/driver/vga.h
 */
#ifndef __VGA_H
#define __VGA_H

#define VGA_MOR_R         0x3cc
#define VGA_MOR_W         0x3c2
#define VGA_ISR_0_R       0x3c2
#define VGA_ISR_1_R       0x3da
#define VGA_FCR_R         0x3ca
#define VGA_FCR_W         0x3da
#define VGA_VSER_W        0x3c3

#define VGA_CRT_ADDR      0x3d4
#define VGA_CRT_DATA      0x3d5
#define VGA_START_ADDR_H  0xc
#define VGA_START_ADDR_L  0xd
#define VGA_CURSOR_H      0xe
#define VGA_CURSOR_L      0xf


#endif