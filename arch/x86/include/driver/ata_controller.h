/*
 * @Author Shi Zhangkun
 * @Date 2020-10-31 21:48:42
 * @LastEditTime 2020-11-14 23:45:34
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/include/driver/ata_controller.h
 */
#ifndef _ATA_CONTROLLER_H
#define _ATA_CONTROLLER_H
#include "yogaOS/types.h"

/* x86 ATA controller have two channels(Primary and Secondary),  and one channel have two port
(master and slave), so can connect 4 HDs at most */
#define ATA_CH_PRIMARY  0x00
#define ATA_CH_SECONDARY 0x01
#define ATA_CH_NUM 2

#define ATA_PORT_MASTER  0x00
#define ATA_PORT_SLAVE 0x01
#define ATA_PORT_PER_CH 2

#define ATA_MODE_LBA_MASK  0x40
#define ATA_SLAVE_PORT_MASK  0x10
#define ATA_HSx_MASK       0x0F

#define ATA_ERR_STAT_MASK 0x01  //bit command execution error
#define ATA_INDEX_STAT_MASK 0x02
#define ATA_ECC_STAT_MASK 0x04  //ECC verify error
#define ATA_DRQ_STAT_MASK 0x08 //data request service
#define ATA_SEEK_STAT_MASK 0x10  //controller seek finish
#define ATA_WRERR_STAT_MASK 0x20  //controller error(write error)
#define ATA_READY_STAT_MASK 0x40  //controller ready to receive command
#define ATA_BUSY_STAT_MASK 0x80   //controller busy

#define ATA_CMD_DEV_RESET     0x08
#define ATA_CMD_RECAL         0x10    // opt nondata recalibrate(low 4bit is step rate)
#define ATA_CMD_READ          0x20    // read sector with retry
#define ATA_CMD_READ_NORT     0x21    // read sector without retry
#define ATA_CMD_READ_L        0x22    // read long(512bytes sector + 4 bytes ECC code) with retry
#define ATA_CMD_READ_L_NORT   0x23    // read long(512bytes sector + 4 bytes ECC code) with retry
#define ATA_CMD_WRITE         0x30    // write sector with retry
#define ATA_CMD_WRITE_NORT    0x31    // write sector without retry
#define ATA_CMD_WRITE_L       0x32    // write long(512bytes sector + 4 bytes ECC code) with retry
#define ATA_CMD_WRITE_L_NORT  0x33    // write long(512bytes sector + 4 bytes ECC code) with retry
#define ATA_CMD_VERIFY        0x40    // req nondata read verify sectors with retry
#define ATA_CMD_VERIFY_NORT   0x41    // req nondata read verify sectors without retry
#define ATA_CMD_FORMAT        0x50    // req vend format track
#define ATA_CMD_CTR_INIT      0x60    // controller init
#define ATA_CMD_SEEK          0x70    // nondata seek(low 4bit is step rate)
#define ATA_CMD_DIAGNOSE      0x90    // req nondata execute drive diagnostics 
#define ATA_CMD_SPECIFY       0x91    // req nondata initialize drive parameters
#define ATA_CMD_IDENTIFY      0xEC    // req PIOin identify drive

typedef struct {
  uint8_t ata_channel;   //primary or secondary
  uint8_t features; // Precompensate before writing
  uint8_t SecCount; 
  uint8_t lbaLow;
  uint8_t lbaMid;
  uint8_t lbaHight;
  uint8_t device;
  uint8_t cmd;
}ataCmd_t;

#endif