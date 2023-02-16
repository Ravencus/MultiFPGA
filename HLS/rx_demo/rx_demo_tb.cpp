/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-15 00:18:28
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-15 11:44:51
 * @FilePath: /MultiFPGA/HLS/rx_demo/rx_demo_tb.cpp
 * @Description: 
 * 
 */

#include<iostream>
#include "hls_stream.h"
#include "rx_demo.h"

int main(){
    hls::stream<pkt> in;
    pkt p_in;
    int save_loc[100];
    // generate data
    for (int i = 0; i < 100; i++)
    {
        p_in.data = i+1;
        p_in.keep = -1;
        p_in.last = i==99?1:0;
        in.write(p_in);
    }
    // call rx_demo
    rx_demo(in, save_loc);
    // check data
    for (int i = 0; i < 100; i++)
    {
        if (save_loc[i] != i+1)
        {
            std::cout << "Error at " << i << std::endl;
            std::cout << "Expected " << i+1 << " but got " << save_loc[i] << std::endl;
            return 1;
        }
    }
    std::cout << "Success" << std::endl;
    return 0;
}