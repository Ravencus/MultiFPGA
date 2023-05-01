
#ifndef RX_KERNEL_H
#define RX_KERNEL_H

#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"

void rx_kernel(hls::stream<ap_axis<16, 1, 1, 1>> &in, hls::stream<ap_fixed<16,3>> &out);

#endif