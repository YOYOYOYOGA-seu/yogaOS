/*
 * @Author Shi Zhangkun
 * @Date 2020-10-01 05:29:37
 * @LastEditTime 2020-11-15 10:26:15
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/arch/x86/driver/x86_ata.c
 */

#include "hd.h"
#include "io.h"
#include "irq.h"
#include "errno.h"
#include "ata_controller.h"
#include "request.h"
#include "yogaOS/req.h"
#include "unistd.h"
#include "stdio.h"
pid_t ataDriverPID = 0;
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
void ata_IRQHandler(void)
{
  IO_inByte(IO_ATA1_STATUS);
  IO_inByte(IO_ATA2_STATUS);
  request_t reqIt = {.ownerPid = ataDriverPID, .type = 0, .length = 0, .pMesg = NULL};
  req_send_it(&reqIt,ataDriverPID);
}

/**
 * @brief  
 * @note  
 * @param {int} port : 0 master 1 slave 
 * @param {int} mod : 0 CHS mode 1 LBA mode 
 * @param {int} lba :  lba addr 
 * @retval none
 */
inline uint8_t ata_creatPortReg(int port, int mod, uint32_t lba)
{
  uint8_t ret = 0;
  if(port > 0)
    ret |= ATA_SLAVE_PORT_MASK;
  if(mod > 0)
    ret |= ATA_MODE_LBA_MASK;
  ret |= (lba>>24)&ATA_HSx_MASK;
  return ret;
}
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
error_t ata_sendCmd(ataCmd_t* cmd)
{
  __disableIRQ();
  if(cmd->ata_channel == ATA_CH_PRIMARY) //Primary ata port
  {
    IO_outByte(0, IO_ATA1_CTR_REG); //enable interrupt
    IO_outByte(cmd->features, IO_ATA1_FEATURES);
    IO_outByte(cmd->SecCount, IO_ATA1_SEC_COUNT);
    IO_outByte(cmd->lbaLow, IO_ATA1_LBA_LOW);
    IO_outByte(cmd->lbaMid, IO_ATA1_LBA_MID);
    IO_outByte(cmd->lbaHight, IO_ATA1_LBA_HIGH);
    IO_outByte(cmd->device, IO_ATA1_DEV);
    IO_outByte(cmd->cmd, IO_ATA1_CMD);
  }
  else  //secondary ata port
  {
    IO_outByte(0, IO_ATA2_CTR_REG); //enable interrupt
    IO_outByte(cmd->features, IO_ATA2_FEATURES);
    IO_outByte(cmd->SecCount, IO_ATA2_SEC_COUNT);
    IO_outByte(cmd->lbaLow, IO_ATA2_LBA_LOW);
    IO_outByte(cmd->lbaMid, IO_ATA2_LBA_MID);
    IO_outByte(cmd->lbaHight, IO_ATA2_LBA_HIGH);
    IO_outByte(cmd->device, IO_ATA2_DEV);
    IO_outByte(cmd->cmd, IO_ATA2_CMD);
  }
  __enableIRQ();
}

/**
 * @brief  
 * @note  
 * @param {hd_t*} hd : hd desc 
 * @param {int} channel : 0 primary 1 secondary 
 * @param {int} port :  0 master 1 slave 
 * @retval none
 */

error_t ata_traverse(hd_t* hd)
{
  if(hd->channel  != ATA_CH_PRIMARY)
    hd->channel = ATA_CH_SECONDARY;
  if(hd->port  != ATA_PORT_MASTER)
    hd->port = ATA_PORT_SLAVE;
  uint32_t offset = hd->channel == 0? 0:(IO_ATA2_DATA - IO_ATA1_DATA);
  uint16_t buf[256];
  request_t reqIt;
  ataCmd_t cmd={
    .device = ata_creatPortReg(hd->port,ATA_MODE_LBA_MASK,0),
    .ata_channel = hd->channel,
    .cmd = ATA_CMD_IDENTIFY,
  };
  if(IO_waitUntilFor(0, ATA_BUSY_STAT_MASK,IO_ATA1_STATUS + offset, 1000) != ENOERR)
    return ETIME;
  ata_sendCmd(&cmd);
  if(reqw_it_for(&reqIt,100) != ENOERR)
    return EIO;
  IO_inWordStream(IO_ATA1_DATA + offset,buf,256);
  if(buf[1] == 0 || buf[3] == 0 || buf[6] == 0)
    return EIO;

  hd->info.generalInfo = buf[0];
  hd->info.numCyls = buf[1];
  hd->info.numHeads = buf[3];
  hd->info.numSectorsPerTrack = buf[6];
  *((uint16_t*)(&hd->info.wCapabilities)) = buf[49];
  hd->info.totalSectors = buf[60] + (((uint32_t)buf[61]) << 16);
  *((uint16_t*)(&hd->info.wCapabilities)) = buf[83];
  hd->size = hd->info.totalSectors * HD_LOGIC_SECTOR_SIZE;
  return ENOERR;
}
/**
 * @brief  
 * @note  
 * @param {*}
 * @retval none
 */
int hd_controllerInit(hd_t* vector)
{
  ataDriverPID = getpid();
  irq_registerExtHandler(HD_IRQ_VECTOR,ata_IRQHandler);
  irq_enableExt(HD_IRQ_VECTOR); //kernel use extern timer irq as it's beats 
  const uint8_t chTrvsIndex[ATA_CH_NUM] = {ATA_CH_PRIMARY,ATA_CH_SECONDARY};
  const uint8_t portTrvsIndex[ATA_PORT_PER_CH] = {ATA_PORT_MASTER,ATA_PORT_SLAVE};
  for(int i = 0,j = 0; i < MAX_HD_NUM&& j < ATA_PORT_PER_CH*ATA_CH_NUM; j++)
  {
    vector[i].channel = chTrvsIndex[j/ATA_PORT_PER_CH];
    vector[i].port = portTrvsIndex[j%ATA_PORT_PER_CH];
    if(ata_traverse(&vector[i]) == ENOERR)
      i++;
  }
}
