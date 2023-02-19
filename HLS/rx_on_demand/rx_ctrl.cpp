/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-19 14:19:06
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 14:48:29
 * @FilePath: /MultiFPGA/HLS/rx_on_demand/rx_ctrl.cpp
 * @Description:
 *
 */

#include "rx_ctrl.h"
#include<iostream>

void rx_ctrl(hls::stream<ap_axis<32, 2, 5, 6>> &in, ap_axis<32, 2, 5, 6> out[1000])
{
#pragma HLS INTERFACE axis port = in
#pragma HLS INTERFACE m_axi port = out bundle = gmem
#pragma HLS INTERFACE s_axilite port = return bundle = control

    ap_axis<32, 2, 5, 6> tmp;

    // tmp.user = 0: data in stream
    // tmp.user = 1: head of stream
    // tmp.user = 2: end of stream
    // tmp.user = 3: terminate

    bool streaming = false;
    int index = 0;
    while (1)
    {
        tmp = in.read();
        if (streaming == false && tmp.user == 1)
        {
            streaming = true;
            out[0] = tmp;
            index = 1;
        }
        else if (streaming == true && tmp.user == 2)
        {
            streaming = false;
            out[index] = tmp;
            index = 0;
        }
        else if (streaming == true && tmp.user != 3)
        {
            out[index] = tmp;
            index++;
        }
        else if (tmp.user == 3)
        {
            return;
        }
    }
}