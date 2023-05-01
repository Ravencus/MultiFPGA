#include <math.h>
#include<stdio.h>

#define C 4     // channel
#define W 23     // IFM_ width
#define H 20    // IFM_ height
#include<math.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"
typedef ap_fixed<16, 3> fm;



void RBN_inf(

	fm op[C][H][W],
	// fm x[C][H][W]
	hls::stream<ap_fixed<16, 3>> &stream_in
)
{

#pragma HLS interface mode=axis port = stream_in  bundle=input
#pragma HLS interface mode=m_axi port = op  bundle=y_op
#pragma HLS INTERFACE s_axilite register port=return


	fm CN = 1;
	fm mean[C];
	fm var[C];
	fm beta[C];
	fm gamma[C];

	for (int i = 0; i < C; i++)
	{
		mean[i] = i;
		var[i] = i;
		beta[i] = i;
		gamma[i] = i;
	}

	// fm x_B[C][H][W];
	// fm op_B[C][H][W];

	// bool tile_full = false;
	ap_fixed<16, 3> dataholder;
	
	ap_fixed<16,3> local_tile[C][H][W];

	int stream_ct = 0;
	int idx_C, idx_W, idx_H;
	int tile_count = 0;
	while (true)
	{
		if (!stream_in.empty())
		{
			dataholder = stream_in.read()
			 
			idx_W = stream_ct % W;
			idx_H = stream_ct / W;
			idx_C = stream_ct / (H*W);

			local_tile[idx_C][idx_H][idx_W] = dataholder;


			stream_ct++;
			if (stream_ct == C*H*W)
			{
				stream_ct = 0;
				// compute RBN
				for (int c = 0; c < C; c+=1)
				{
					for (int h = 0; h < H; h++)
					{
						for (int w = 0; w < W; w++)
						{
								op[c][h][w] = (local_tile[c][h][w] - mean[c]) / var[c] / CN * gamma[c] + beta[c];
						}
					}
				}
				tile_count+=1;
				if (tile_count == 16*32*16){
					return;
				}
			}
		}
		else
		{
			continue;
		}
			
	}



	

	// for (int c = 0; c < C; c++)
	// {
	// 	for (int h = 0; h < H; h++)
	// 	{
	// 		for (int w = 0; w < W; w++)
	// 		{
	// 			op[c][h][w] = op_B[c][h][w];
	// 		}

	// 	}

	// }

    return;
}





