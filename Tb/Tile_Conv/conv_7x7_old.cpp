///////////////////////////////////////////////////////////////////////////////
// Author:      <>
// Course:      ECE8893 - Parallel Programming for FPGAs
// Filename:    conv_7x7.cpp
// Description: Implement a functionally-correct synthesizable 7x7 convolution 
//              for a single tile block without any optimizations
///////////////////////////////////////////////////////////////////////////////
#include "utils.h"

void conv_7x7 (
    fm_t Y_buf[OUT_BUF_DEPTH][OUT_BUF_HEIGHT][OUT_BUF_WIDTH], 
    fm_t X_buf[IN_BUF_DEPTH][IN_BUF_HEIGHT][IN_BUF_WIDTH],
    wt_t W_buf[OUT_BUF_DEPTH][IN_BUF_DEPTH][KERNEL_HEIGHT][KERNEL_WIDTH],
    wt_t B_buf[OUT_BUF_DEPTH]
)
{
#pragma HLS inline off

//---------------------------------------------------------------------------
// Part B: Implement a trivial functionally-correct single-tile convolution.
//
//         This should have an overall latency in the order of 22-23 seconds.
//
//         If it's worse than trivial, it may be worth fixing this first.
//         Otherwise, achieving the target latency with a worse-than-trivial
//         baseline may be difficult!
//
// TODO: Your code for Part B goes here. 
//---------------------------------------------------------------------------
    
    // int height_offset = OFbuffer_h*STRIDE;

    for (int filter_num=0; filter_num < OUT_BUF_DEPTH; filter_num++) // no of filter. Also the first dimension of OFM 
    {
        for (int OFbuffer_h =0; OFbuffer_h < OUT_BUF_HEIGHT; OFbuffer_h++)  // OFM_height
        {
            for (int OFbuffer_w=0; OFbuffer_w < OUT_BUF_WIDTH; OFbuffer_w++)    // OFM_width
            {
                for (int IFbuffer_dep = 0; IFbuffer_dep < IN_BUF_DEPTH; IFbuffer_dep++)    // IFM_depth
                {
                    for (int fil_h=0; fil_h < KERNEL_HEIGHT; fil_h++)   // filter height
                    {
                        for (int fil_w=0; fil_w < KERNEL_WIDTH; fil_w++)    // filter width
                        {
                            Y_buf[filter_num][OFbuffer_h][OFbuffer_w] += X_buf[IFbuffer_dep][OFbuffer_h*STRIDE + fil_h][OFbuffer_w*STRIDE + fil_w] *\
                                W_buf[filter_num][IFbuffer_dep][fil_h][fil_w];
                                
                        }
                    }
                }

                Y_buf[filter_num][OFbuffer_h][OFbuffer_w] += B_buf[filter_num];
            }
        }
    }



}
