/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-15 00:18:08
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-15 11:52:02
 * @FilePath: /MultiFPGA/HLS/rx_demo/rx_demo.cpp
 * @Description: 
 * 
 */

#include "rx_demo.h"

void rx_demo(hls::stream<pkt> &in, int save_loc[100]){
    #pragma HLS INTERFACE axis port=in
    #pragma HLS INTERFACE m_axi port=save_loc bundle=gmem
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    pkt p_in;
    int i = 0;
    do {
        p_in = in.read();
        save_loc[i] = p_in.data;
        i++;
    } while (!p_in.last);
}