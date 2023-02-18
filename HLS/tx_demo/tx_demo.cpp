/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-15 00:04:03
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-15 00:13:37
 * @FilePath: /MultiFPGA/HLS/tx_demo/tx_demo.cpp
 * @Description: 
 *     simple demo for verifing the tx function
 *     Generate a array from 1 to 100, and send it to tx channel
 */

#include "tx_demo.h"

void tx_demo(hls::stream<pkt> &out){
    #pragma HLS INTERFACE axis port=out
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    pkt p_out;
    for (int i = 0; i < 100; i++)
    {
        p_out.data = i+1;
        p_out.keep = -1;
        p_out.last = i==99?1:0;
        out.write(p_out);
    }
}