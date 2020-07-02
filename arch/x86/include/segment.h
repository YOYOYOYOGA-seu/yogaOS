/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 21:59:46
 * @LastEditTime 2020-03-28 05:06:07
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/segment.h
 */
#ifndef __SEGMENT_H
#define __SEGMENT_H

#include "address.h"
#include "types.h"
#include "errno.h"
/* ------------------------ type define --------------------------- */
typedef uint16_t selector_t;



typedef struct{
  uint16_t limit_l_16bit;
  uint16_t baseAddr_byte1_2;
  uint8_t baseAddr_byte3;
  uint8_t TYPE_S :5;
  uint8_t DPL :2;
  uint8_t P :1;
  uint8_t limit_h_4bit :4;
  uint8_t AVL :1;
  uint8_t zeroBit :1;
  uint8_t D_B :1;
  uint8_t G :1;
  uint8_t baseAddr_byte4;
}memSegDesc_t;

typedef enum{
  DESC_DPL_0 = 0,
  DESC_DPL_1,
  DESC_DPL_2,
  DESC_DPL_3
}descDPL_t;

typedef struct{
  uint16_t offset_byte1_2;
  uint16_t selector;
  uint8_t paramCount :5;
  uint8_t zeroBit :3;
  uint8_t TYPE_S :5;
  uint8_t DPL :2;
  uint8_t P :1;
  uint16_t offset_byte3_4;
}gateDesc_t;

typedef enum{
  DESC_TYPE_286TSS_A = 1,
  DESC_TYPE_LDT,
  DESC_TYPE_286TSS_B,
  DESC_TYPE_286GATE_C,
  DESC_TYPE_TASK,
  DESC_TYPE_286GATE_I,
  DESC_TYPE_286GATE_TR,
  DESC_TYPE_386TSS_A = 9,
  DESC_TYPE_386TSS_B = 11,
  DESC_TYPE_386GATE_C,     //i386 call gate
  DESC_TYPE_386GATE_I = 14, // i386 irq gate
  DESC_TYPE_386GATE_TR,      //i386 trap gate

  DESC_TYPE_Read = 16, //read only
  DESC_TYPE_Read_A,   //read only, have been accessed
  DESC_TYPE_RW,        
  DESC_TYPE_RW_A,
  DESC_TYPE_R_DOWN,   //read only, scaling down
  DESC_TYPE_R_DOWN_A,
  DESC_TYPE_RW_DOWN,
  DESC_TYPE_RW_DOWN_A,
  DESC_TYPE_C,        //Code and can only be operated
  DESC_TYPE_C_A,
  DESC_TYPE_CR,        //Code and can be read
  DESC_TYPE_CR_A,
  DESC_TYPE_CCO,
  DESC_TYPE_CCO_A,
  DESC_TYPE_CCOR,
  DESC_TYPE_CCOR_A
}descType_t;

typedef memSegDesc_t ldtDesc_t;
typedef memSegDesc_t tssDesc_t;
typedef gateDesc_t callGateDesc_t;
typedef gateDesc_t irqGateDesc_t;
typedef gateDesc_t trapGateDesc_t;
/* -------------------------- define ----------------------------- */
#define INIT_GDT_NUM           3
#define INIT_LDT_NUM           3
#define LDT_SIZE               (INIT_LDT_NUM * 8)
#define LDT_DPL                DESC_DPL_3

#define SEL_TI_MASK            0x04
/* ------------------------ function declare --------------------------- */
uint16_t seg_getGdtNum(void);
selector_t seg_addDescToGDT(uint32_t baseAddr, uint32_t length, descDPL_t dpl,descType_t type,uint8_t d_b_bit);
error_t seg_initDesc(memSegDesc_t *desc, uint32_t baseAddr, uint32_t length, descDPL_t dpl,descType_t type,uint8_t d_b_bit);
error_t seg_initGate(gateDesc_t *desc, uint32_t offsetAddr, selector_t sel, descDPL_t dpl,descType_t type);
void seg_initGDTStruct(void);


#endif
