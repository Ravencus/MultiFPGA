/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-12 14:41:40
 * @LastEditors: ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-12 18:14:31
 * @FilePath: /MultiFPGA/HLS/memory_kernel/mem_sfpp.h
 * @Description: 
 * 
 */

#ifndef __MEM_SFPP_H__
#define __MEM_SFPP_H__

#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

typedef ap_axiu<32, 1, 1, 1> pkt;

void mem_sfpp(hls::stream<pkt> &in, hls::stream<pkt> &out);

#endif