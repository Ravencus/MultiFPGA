/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-12 14:42:52
 * @LastEditors: ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-12 18:18:19
 * @FilePath: /MultiFPGA/HLS/memory_kernel/tb_mem_sfpp.cpp
 * @Description: 
 * 
 */

#include "mem_sfpp.h"
#include <iostream>
#include "hls_stream.h"

using namespace std;

int main(){
    hls::stream<pkt> in;
    hls::stream<pkt> out;
    pkt p_in;
    pkt p_out;
    // create int 32 array of size 1000
    uint32_t data[1000];
    // randomly generate int for data
    for (int i = 0; i < 1000; i++)
    {
        data[i] = rand();
    }

    // transfer data to in
    for (int i = 0; i < 1000; i++)
    {
        p_in.data = data[i];
        p_in.keep = -1;
        p_in.last = i==999?1:0;
        in.write(p_in);
    }
    // call mem_sfpp
    mem_sfpp(in, out);

    uint32_t data_out[1000];
    // transfer data from out
    for (int i = 0; i < 1000; i++)
    {
        p_out = out.read();
        data_out[i] = p_out.data;
    }

    // compare data and data_out
    for (int i = 0; i < 1000; i++)
    {
        if (data[i] != data_out[i])
        {
            cout << "Error at " << i << endl;
            return 1;
        }
    }
    cout << "Success" << endl;

    // cout first 5 elements
    for (int i = 0; i < 5; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << data_out[i] << " ";
    }
    cout << endl;

}