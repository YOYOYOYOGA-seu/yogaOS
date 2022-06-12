/*
 * @Author Shi Zhangkun
 * @Date 2020-10-24 21:01:44
 * @LastEditTime 2022-06-12 14:48:41
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/driver/hd.h
 */

#ifndef __HD_H
#define __HD_H

#include "yogaOS/types.h"
#include "yogaOS/dev.h"

#define MAX_HD_NUM 4
#define HD_LOGIC_SECTOR_SIZE   512   //default logic sector size(LBA28)
#define HD_MBR_DPT_OFFSET    0x01BE
#define HD_TYPE_ASCII_SIZE   40
#define HD_SERIAL_ASCII_SIZE 20

typedef enum {
  HD_CMD_READ,
  HD_CMD_WRITE,
  HD_CMD_FORMAT
}hdOprType_t;

typedef struct 
{
  uint16_t generalInfo;   // WORD 0
  uint16_t numCyls;       // WORD 1
  uint16_t numHeads;      // WORD 3
  uint16_t numSectorsPerTrack;  // WORD 6
  char serialNum[HD_SERIAL_ASCII_SIZE];  // WORD 10-19
  char modelNumber[HD_TYPE_ASCII_SIZE]; // WORD 27-46
  struct {
  uint16_t reserved1:8;
  uint16_t dma:1; // 1 = support DMA
  uint16_t lba:1;  // 1 = support LBA
  uint16_t disIORDY:1; // 1 = don't require IORDY
  uint16_t IORDY:1;   // 1 = support IORDY
  uint16_t softReset:1; // 1 = nead ATA soft reset
  uint16_t overlap:1; // 1= support overlapped operation
  uint16_t queue:1; // 1=support cmd queue
  uint16_t inlDMA:1; // 1=support Cross access DMA
  } wCapabilities;   // WORD 49
  uint32_t totalSectors;  // WORD 60-61
  struct {
    uint16_t reserved2:9;
    uint16_t lba48:1;
    uint16_t reserved3:6;
  } cmdSetSpport;  // WORD 83
}hdInfo_t;


typedef struct{
  uint64_t size;
  hdInfo_t info;
  uint8_t channel;  //used to flag access channel
  uint8_t port; //used to flag the hd index in the access channel(some arch like x86 one channel can connect two or more hard disk)
  uint8_t valid;
  devNumber_t devNum;
  uint8_t dpt[4][16];
}hd_t;

typedef struct {
  hdOprType_t cmd;
  void *dest;
  int startSec;
  int counts;
  int secSize;
}hdOperate_t;

/* ------------------------------Arch relevant function  ----------------------------- */
int hd_controllerInit(hd_t* vector);
int hd_operate(const hd_t* hd, hdOperate_t ctl);
/* ------------------------------function declaration ----------------------------- */
error_t hd_init(void);
error_t hd_read(size_t hd, void *dest, size_t size);
error_t hd_write(size_t hd, void *dest, size_t size);
#endif