/*
 * @Author Shi Zhangkun
 * @Date 2020-02-17 21:58:40
 * @LastEditTime 2020-02-29 04:58:22
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/mm/segment.c
 */

#include "segment.h"
/* Define ---------------------------------------------------------- */
#define NUM_OF_GDT_STATE_MAP_ARRY       (GDT_AREA_SIZE)/(sizeof(uint32_t)*sizeof(memSegDesc_t))

/* variable and strcut ---------------------------------------------- */
/* struct to manage GDT ,we ranged the Descriptor in GDT from 0 ~ Max - 1, and the 
0 respect the first zero descriptor */
volatile struct{
  uint16_t descNum;
  /* Creat a continuous memory area to sign the state(using/idle) of every descriptor
    in the GDT. Using bit to sign */
  uint32_t gdtStateMap[NUM_OF_GDT_STATE_MAP_ARRY] ;
  
}GDT;


/**
 * @brief  init a descriptor
 * @note  
 * @param {memSegDesc_t *} desc :point to the Descriptor
 *        {uint32_t} baseAddr :Base address of the segment 
 *        {uint32_t} length   :length of the segment
 *        {descDPL_t} dpl     :Descriptor Privilege Level
 *        {descType_t}type    :type of descriptor
 *        {uintt8_t}d_b_bit   :the D/B bit  when the desc type is code, it
 *                            represent the code is 32bit( = 1) or 16bit(= 0)
 * @retval error_t
 */
error_t mm_initDesc(memSegDesc_t *desc, uint32_t baseAddr, uint32_t length,\
                     descDPL_t dpl,descType_t type,uint8_t d_b_bit )
{
  if(type < DESC_TYPE_Read && type != DESC_TYPE_LDT     \
              && type != DESC_TYPE_386TSS_A && type != DESC_TYPE_386TSS_B)
  {
    return EPERM ;
  }
  desc->baseAddr_byte1_2 = (uint16_t)( baseAddr & 0xffff);
  baseAddr = baseAddr>>16;
  desc->baseAddr_byte3 = (uint8_t)(baseAddr & 0xff);
  baseAddr = baseAddr>>8;
  desc->baseAddr_byte4 = (uint8_t)(baseAddr & 0xff);
  if(length <= 0xfffff)
  {
    desc->G = 0;
    desc->limit_l_16bit = (uint16_t)(length & 0xffff);
    length = length>>16;
    desc->limit_h_4bit = (uint8_t)(length & 0x000f);
  }
  else
  {
    desc->G = 1;
    length = length>>12;
    desc->limit_l_16bit = length;
    length = length>>16;
    desc->limit_h_4bit = (uint8_t)(length & 0x000f);
  }
  desc->D_B = d_b_bit;
  desc->DPL = dpl;
  desc->P = 1;
  desc->AVL = 0;
  desc->TYPE_S = type;
  desc->zeroBit = 0;
  return ENOERR;
}

/**
 * @brief  init a Gate descriptor
 * @note  
 * @param {memSegDesc_t *} desc :point to the Gate Descriptor
 *        {uint32_t} offsetAddr :The code addr offset in the segment
 *        {selector_t} sel   :selector of the segment which the code localed
 *        {descDPL_t} dpl     :Descriptor Privilege Level
 *        {descType_t}type    :type of descriptor
 * @retval error_t
 */
error_t initGate(gateDesc_t *desc, uint32_t offsetAddr,\
                     selector_t sel, descDPL_t dpl,descType_t type)
{
  if(type != DESC_TYPE_386GATE_C && type != DESC_TYPE_386GATE_TR && type != DESC_TYPE_386GATE_I)
  {
    return EPERM ;
  }
  desc->offset_byte1_2 = (offsetAddr&0xffff);
  desc->offset_byte3_4 = (offsetAddr>>16)&0xffff;
  desc->DPL = dpl;
  desc->P = 1;
  desc->paramCount = 0;
  desc->TYPE_S = type;
  desc->zeroBit = 0;
  desc->selector = sel;
}

static volatile uint16_t gdtNum = INIT_GDT_NUM;
/**
 * @brief  mm_getGdtNum
 * @note  
 * @param {type} none
 * @retval The total number of descriptor in GDT
 */
uint16_t mm_getGdtNum(void)
{
  return GDT.descNum;
}

/**
 * @brief  Set the bit which represent the GDT descriptor's state(using/idle) 
 * @note  
 * @param {uint16_t} number   :the index of the desc in GDT
 *        {uint16_t} state    :0 idle, 1 busy
 * @retval error_t
 */
static error_t setGDTdescState(uint16_t num, uint16_t state)
{
  uint16_t index, bitNum;
  uint32_t lastStateMap;
  index = num/(8*sizeof(uint32_t));
  bitNum = num%(8*sizeof(uint32_t));
  lastStateMap = GDT.gdtStateMap[index];
  if(!state)
    GDT.gdtStateMap[index] &= ~(0x01<<bitNum);
  else
    GDT.gdtStateMap[index] |= 0x01<<bitNum; 

  if(GDT.gdtStateMap[index] == lastStateMap)
    return EPERM;
  else
    return ENOERR;
  
}

/**
 * @brief  free a descriptor in GDT
 * @note  
 * @param {uint16_t} num   :the index of the desc in GDT
 * @retval error_t
 */
static error_t freeDescInGDT(uint16_t num)
{
  if(setGDTdescState(num,0) == ENOERR)
  {
    GDT.descNum --;
    return ENOERR;
  }
  else
    return EPERM;
  
}

/**
 * @brief  Alloc a descriptor in GDT
 * @note  
 * @param {type} none
 * @retval the index of this descriptor in GDT.
 *         if 0, represent alloc failed
 */
static uint16_t allocDescInGDT(void)
{
  uint16_t i,j,descIndex;
  uint32_t temp;
  
  for(i = 0; i < NUM_OF_GDT_STATE_MAP_ARRY; i++)
  {
    if(GDT.gdtStateMap[i] != ~((uint32_t)0))
    {
      goto travrseMap;
    }
  }
  goto noIdleDesc;
  
travrseMap:
  temp = GDT.gdtStateMap[i];
  for(j = 0; j < 8*sizeof(uint32_t) ; j++)
  {
    if(!(temp & 0x01))
    {
      descIndex = 8 * i + j;
      goto findIdleDesc;
    }
    temp = temp >> 1;
  }
  
noIdleDesc:
  return 0;
findIdleDesc:
  GDT.descNum ++;
  setGDTdescState(descIndex,1);
  return descIndex;
}

/**
 * @brief  Add a new desc to GDT
 * @note  
 * @param {uint32_t} baseAddr :Base address of the segment 
 *        {uint32_t} length   :length of the segment
 *        {descDPL_t} dpl     :Descriptor Privilege Level
 *        {descType_t}type    :type of descriptor
 *        {uintt8_t}d_b_bit   :the D/B bit 
 * @retval selector_t
 */
selector_t mm_addDescToGDT(uint32_t baseAddr, uint32_t length,\
                     descDPL_t dpl,descType_t type,uint8_t d_b_bit)
{
  error_t flag;
  uint16_t descNum;
  memSegDesc_t *temp =  (memSegDesc_t *)(GDT_BASE_ADDR);
  descNum = allocDescInGDT();
  if(descNum)
  {
    temp += descNum;
    if(mm_initDesc(temp,baseAddr,length,dpl,type,d_b_bit) != ENOERR)
      return 0;
  }
  else
  {
    return 0;
  }
  return (descNum << 3) + dpl;
}

/**
 * @brief  init GDT strcut
 * @note  
 * @param {type} none
 * @retval none
 */
void mm_initGDTStruct(void)
{
  int i;
  GDT.descNum = INIT_GDT_NUM;
  for(i = 0; i < INIT_GDT_NUM; i++)
    setGDTdescState(i, 1);
}

