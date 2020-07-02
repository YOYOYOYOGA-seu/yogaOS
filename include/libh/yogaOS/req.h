/*
 * @Author Shi Zhangkun
 * @Date 2020-06-27 01:52:47
 * @LastEditTime 2020-06-27 04:27:16
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/yogaOS/req.h
 */ 
#ifndef __REQ_H
#define __REQ_H
#include "types.h"


/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
unsigned int reqw(request_t * req);
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t reqa(request_t * req);
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t reqs(request_t * req, pid_t dest);
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t reqr(request_t * req);
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
error_t reqt(request_t * req, pid_t dest);
#endif