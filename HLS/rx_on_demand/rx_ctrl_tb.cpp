/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-19 14:19:23
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 14:48:16
 * @FilePath: /MultiFPGA/HLS/rx_on_demand/rx_ctrl_tb.cpp
 * @Description:
 *
 */

#include "rx_ctrl.h"
#include <iostream>

int main()
{
    hls::stream<ap_axis<32, 2, 5, 6>> in;
    ap_axis<32, 2, 5, 6> tmp;
    ap_axis<32, 2, 5, 6> out[1000];

    // before streaming start, generate 100 data with user = 0
    for (int i = 0; i < 100; i++)
    {
        tmp.data = i;
        tmp.user = 0;
        in.write(tmp);
    }

    // streaming start, generate 1000 data with first element user = 1, last element user = 2
    tmp.data = 100;
    tmp.user = 1;
    in.write(tmp);

    for (int i = 1; i < 999; i++)
    {
        tmp.data = i + 100;
        tmp.user = 0;
        in.write(tmp);
    }

    tmp.data = 999 + 100;
    tmp.user = 2;
    in.write(tmp);

    // after streaming end, send a data with user = 3 to terminate
    tmp.data = 0;
    tmp.user = 3;
    in.write(tmp);

    // call rx_ctrl
    rx_ctrl(in, out);

    bool success = true;

    // check data
    for (int i = 0; i < 1000; ++i)
    {
        if (out[i].data != i + 100)
        {
            std::cout << "data is not correct!" << std::endl;
            std::cout << "out[" << i << "].data = " << out[i].data << std::endl;
            std::cout << "expecting " << i + 100 << std::endl;
            success = false;
        }
    }

    if (success)
        std::cout << "Test passed!" << std::endl;
    else
        std::cout << "Test failed!" << std::endl;
    return 0;
}