/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-19 14:19:12
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 16:28:10
 * @FilePath: /MultiFPGA/HLS/rx_on_demand/rx_ctrl.h
 * @Description: 
 * 
 */
#ifndef RX_CTRL_H
#define RX_CTRL_H

#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"

void rx_ctrl(hls::stream<ap_axis<32, 2, 5, 6>> &in, ap_int<32> out[1000]);

#endif