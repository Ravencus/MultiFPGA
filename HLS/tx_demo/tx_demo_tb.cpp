/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-15 00:04:06
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-15 00:13:51
 * @FilePath: /MultiFPGA/HLS/tx_demo/tx_demo_tb.cpp
 * @Description:
 *     Testbench for tx_demo
 */
#include <iostream>
#include "hls_stream.h"
#include "tx_demo.h"


int main(){
    hls::stream<pkt> out;
    pkt p_out;
    // call tx_demo
    tx_demo(out);
    // transfer data from out
    for (int i = 0; i < 100; i++)
    {
        p_out = out.read();
        if (p_out.data != i+1)
        {
            std::cout << "Error at " << i << std::endl;
            std::cout << "Expected " << i+1 << " but got " << p_out.data << std::endl;
            return 1;
        }
    }

    std::cout << "Success" << std::endl;

    return 0;
}