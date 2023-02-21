/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-12 14:42:15
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-19 13:09:41
 * @FilePath: /HLS/memory_kernel/mem_sfpp.cpp
 * @Description: 
 * 
 */

#include "mem_sfpp.h"

void mem_sfpp(hls::stream<pkt> &in, hls::stream<pkt> &out) {
    #pragma HLS INTERFACE mode=axis port=in
    #pragma HLS INTERFACE mode=axis port=out
    #pragma HLS INTERFACE mode=s_axilite port=return bundle=control


}