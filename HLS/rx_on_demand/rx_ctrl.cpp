/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-19 14:19:06
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 22:32:00
 * @FilePath: /MultiFPGA/HLS/rx_on_demand/rx_ctrl.cpp
 * @Description:
 *
 */

#include "rx_ctrl.h"

void rx_ctrl(hls::stream<ap_axis<32, 2, 5, 6>> &in, ap_int<32> store_DRAM[1000])
{
#pragma HLS INTERFACE axis port = in
#pragma HLS INTERFACE m_axi port = store_DRAM offset=slave bundle = gmem
#pragma HLS INTERFACE s_axilite port = store_DRAM bundle = control
#pragma HLS INTERFACE s_axilite port = in bundle = control

#pragma HLS INTERFACE s_axilite port = return bundle = control


    ap_axis<32, 2, 5, 6> tmp;
    ap_int<32> data[1000];

    ap_int<32> rx_count = 0;
    // init data
    INIT:
    for (int i = 0; i < 1000; i++)
    {
        data[i] = 0;
    }

    READ:
    while (true)
    {
        if (in.empty())
        {
            continue;
        }
        else
        {
            tmp = in.read();
            data[rx_count] = tmp.data;
            rx_count++;
        }
        if(rx_count == 1000)
        {
            break;
        }
    }
    int i=0;
    if (rx_count == 1000){
        // write back
        WB1:
        for (; i < 1000;)
        {
            store_DRAM[i] = 0;
            i++;

        }
        rx_count = 1001;
    }
    i=0;
    if (rx_count == 1001){
        // write back
        WB2:
        for (; i < 1000;)
        {
            store_DRAM[i] = 1;
            i++;
        }
        rx_count = 1002;
    }

    return;
}