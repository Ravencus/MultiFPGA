/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-17 00:55:17
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-20 22:45:39
 * @FilePath: /MultiFPGA/HLS/tx_on_demand/tx_ctrl.cpp
 * @Description:
 *
 */
#include "tx_ctrl.h"

void tx_ctrl(hls::stream<ap_axis<32, 2, 5, 6>> &out, ap_int<32> local_copy[1000])
{
#pragma HLS INTERFACE m_axi port = local_copy offset = slave bundle = gmem
#pragma HLS INTERFACE axis port = out

#pragma HLS INTERFACE s_axilite port = local_copy bundle = control
#pragma HLS INTERFACE s_axilite port = out bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

    ap_int<32> tx_count = 0;
    ap_int<32> data[1000];

    for (int i = 0; i < 1000; i++)
    {
        data[i] = 500 - i;
    }

    // send three 7777 as head
    for (int i = 0; i < 4; i++)
    {
        ap_axis<32, 2, 5, 6> tmp;
        tmp.data = 7777;
        tmp.last = 0;
        tmp.user = 0;
        tmp.id = 0;
        out.write(tmp);
    }


    // send data to out
    for (int i = 0; i < 1000; i++)
    {
        ap_axis<32, 2, 5, 6> tmp;
        tmp.data = data[i];
        out.write(tmp);
    }

    // copy data to local_copy
    for (int i = 0; i < 1000; i++)
    {
        local_copy[i] = data[i];
    }

    return;
}