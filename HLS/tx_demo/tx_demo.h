/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-15 00:13:14
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-15 00:13:25
 * @FilePath: /MultiFPGA/HLS/tx_demo/tx_demo.h
 * @Description:    
 * 
 */

#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

typedef ap_axiu<32, 1, 1, 1> pkt;

void tx_demo(hls::stream<pkt> &out);