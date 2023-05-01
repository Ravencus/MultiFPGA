#include "rx_kernel.h"

void rx_kernel(hls::stream<ap_axis<16, 1, 1, 1>> &in, hls::stream<ap_fixed<16,3>> &out)
{
#pragma HLS INTERFACE axis port = in
#pragma HLS INTERFACE s_axilite port = in bundle = control
#pragma HLS INTERFACE axis port = out
#pragma HLS INTERFACE s_axilite port = out bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

    while(true)
    {
        if(in.empty())
        {
            continue;
        }
        else
        {
            ap_axis<16, 1, 1, 1> tmp;
            tmp = in.read();
            ap_int<16> raw = tmp.data;
            ap_fixed<16, 3> fp;
            for (int t = 0; t < 16; t++)
            {
                fp[t] = raw[t];
            }
            out.write(fp);
        }
    }


}