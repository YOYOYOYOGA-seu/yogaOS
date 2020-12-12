/*
 * @Author Shi Zhangkun
 * @Date 2020-06-27 01:52:47
 * @LastEditTime 2020-11-15 06:07:43
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/include/libh/yogaOS/req.h
 */ 
#ifndef __REQ_H
#define __REQ_H
#include "yogaOS/types.h"

#define REQ_TYPE_IT 0xFFFFFFFF

error_t reqw(request_t * req);

error_t reqw_for(request_t * req, uint32_t wait);

error_t reqw_it(request_t * req);

error_t reqw_it_for(request_t * req, uint32_t wait);

error_t reqa(request_t * req);

error_t reqs(request_t * req, pid_t dest);

error_t reqs_for(request_t * req, pid_t dest, uint32_t wait);

error_t reqt(request_t * req, pid_t dest);
#endif