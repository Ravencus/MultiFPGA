/*
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-17 00:55:17
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-17 00:58:57
 * @FilePath: /HLS/txrx_single/txrx.cpp
 * @Description: 
 * 
 */
#include "ap_axi_sdata.h"
#include "hls_stream.h"

void txrx(hls::stream<ap_axis<32,2,5,6> > &in, hls::stream<ap_axis<32,2,5,6> > &out)
{
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE s_axilite port=return

ap_axis<32,2,5,6> tmp;

while(1)
{
    in.read(tmp);
    tmp.data = tmp.data + 5;
    out.write(tmp);
    if(tmp.last)
    {
        break;
    }
        
}

}