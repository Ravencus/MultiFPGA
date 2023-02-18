/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-12 14:42:15
 * @LastEditors: ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-12 18:15:12
 * @FilePath: /MultiFPGA/HLS/memory_kernel/mem_sfpp.cpp
 * @Description: 
 * 
 */

#include "mem_sfpp.h"

void mem_sfpp(hls::stream<pkt> &in, hls::stream<pkt> &out) {
    #pragma HLS INTERFACE mode=axis port=in
    #pragma HLS INTERFACE mode=axis port=out
    #pragma HLS INTERFACE mode=s_axilite port=return bundle=control

    for(bool eos=false; eos==false; ){
        // #pragma HLS PIPELINE II=1
        pkt p_in;
        pkt p_out;
        in.read(p_in);
        p_out.data = p_in.data;
        p_out.keep = p_in.keep;
        p_out.last = p_in.last;
        out.write(p_out);
        if (p_in.last)
        {
            eos = true;
        }
    }

}