/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-19 13:41:20
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 14:16:24
 * @FilePath: /MultiFPGA/HLS/tx_on_demand/tx_ctrl_tb.cpp
 * @Description: 
 * 
 */
#include "tx_ctrl.h"

#include <iostream>

int main()
{
    hls::stream<ap_axis<32, 2, 5, 6>> out;
    ap_int<32> tx_count = 1;

    // call tx_send
    tx_send(tx_count, out);
    
    ap_int<32> recv_data[1000];
    ap_uint<2> recv_user[1000];
    ap_axis<32, 2, 5, 6> tmp;

    // read data
    for (int i = 0; i < 1000; i++)
    {
        tmp = out.read();
        recv_data[i] = tmp.data;
        recv_user[i] = tmp.user;
    }

    // check data
    for (int i = 0; i < 1000; i++)
    {
        if (recv_data[i] != i + tx_count * 1000)
        {
            std::cout << "data is not correct!" << std::endl;
            std::cout << "recv_data[" << i << "] = " << recv_data[i] << std::endl;
            std::cout << "expecting " << i + tx_count * 1000 << std::endl;
            return -1;
        }

        if (i == 0 && recv_user[i] != 1)
        {
            std::cout << "user data "<< i <<" is not correct!" << std::endl;
            std::cout << "recv_user[" << i << "] = " << recv_user[i] << std::endl;
            std::cout << "expecting " << 1 << std::endl;
            return -1;
        }
        else if (i == 999 && recv_user[i] != 2)
        {
            std::cout << "user data "<< i <<" is not correct!" << std::endl;
            std::cout << "recv_user[" << i << "] = " << recv_user[i] << std::endl;
            std::cout << "expecting " << 2 << std::endl;
            return -1;
        }
        else if ( i != 0 && i != 999 && recv_user[i] != 0)
        {
            std::cout << "user data "<< i <<" is not correct!" << std::endl;
            std::cout << "recv_user[" << i << "] = " << recv_user[i] << std::endl;
            std::cout << "expecting " << 0 << std::endl;
            return -1;
        }
    }


    std::cout << "--------------------------" << std::endl;
    std::cout << "|TEST for tx_send PASSED!|" << std::endl;
    std::cout << "--------------------------" << std::endl;
}