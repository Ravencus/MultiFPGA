/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-19 13:58:01
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 14:07:29
 * @FilePath: /HLS/tx_on_demand/tx_ctrl.h
 * @Description: 
 * 
 */

#ifndef TX_CTRL_H
#define TX_CTRL_H

#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"
void tx_send(ap_int<32> tx_count, hls::stream<ap_axis<32, 2, 5, 6>> &out);
void tx_ctrl(bool write[2], hls::stream<ap_axis<32, 2, 5, 6>> &out);

#endif