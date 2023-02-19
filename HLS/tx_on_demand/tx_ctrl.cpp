/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-17 00:55:17
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 14:51:47
 * @FilePath: /MultiFPGA/HLS/tx_on_demand/tx_ctrl.cpp
 * @Description:
 *
 */
#include "tx_ctrl.h"

void tx_send(ap_int<32> tx_count, hls::stream<ap_axis<32, 2, 5, 6>> &out){
    ap_axis<32, 2, 5, 6> tmp;
    ap_int<32> tx_data[1000];
    for (int i = 0; i < 1000; i++)
        {
            tx_data[i] = i + tx_count * 1000;
        }
        tx_count++;

        tmp.data = tx_data[0];
        tmp.user = 1;
        out.write(tmp);

        for (int i = 1; i < 999; i++)
        {
            tmp.data = tx_data[i];
            tmp.user = 0;
            out.write(tmp);
        }

        tmp.data = tx_data[999];
        tmp.user = 2;
        out.write(tmp);


}

void tx_ctrl(bool write[2], hls::stream<ap_axis<32, 2, 5, 6>> &out)
{
#pragma HLS INTERFACE m_axi port = write bundle = gmem
#pragma HLS INTERFACE axis port = out
#pragma HLS INTERFACE s_axilite port = return

    ap_int<32> tx_count = 0;

    while (1)
    {
        bool write_0 = write[0];
        bool write_1 = write[1];

        if (write_0 == 0 && write_1 == 0)
        {
            // send data with user = 3 to terminate
            ap_axis<32, 2, 5, 6> tmp;
            tmp.data = 0;
            tmp.user = 3;
            out.write(tmp);

            break;
        }
        else if (write_0 == 0 || write_1 == 0)
        {
            continue;
        }

        write[0] = 0;
        write[1] = 1;

        tx_send(tx_count, out);

        
    }
}