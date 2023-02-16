/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-15 00:13:14
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-15 11:50:35
 * @FilePath: /MultiFPGA/HLS/rx_demo/rx_demo.h
 * @Description:    
 * 
 */

#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

typedef ap_axiu<32, 1, 1, 1> pkt;

void rx_demo(hls::stream<pkt> &in, int save_loc[100]);