#include <math.h>
#include<stdio.h>

#define C 4     // channel
#define W 23     // IFM_ width
#define H 20    // IFM_ height
#include<math.h>
#include <ap_fixed.h>

typedef ap_fixed<16, 3> fm;



void RBN_inf(

	fm op[C][H][W],
	fm x[C][H][W]
)
{

#pragma HLS interface mode=m_axi port = x  bundle=x_ip
#pragma HLS interface mode=m_axi port = op  bundle=y_op
#pragma HLS INTERFACE s_axilite register port=return

// #pragma HLS interface mode=m_axi offset=slave bundle=C port=mean
// #pragma HLS interface mode=m_axi offset=slave bundle=D port=var
// #pragma HLS interface mode=m_axi offset=slave bundle=C port=CN
// #pragma HLS interface mode=m_axi offset=slave bundle=D port=beta
// #pragma HLS interface mode=m_axi offset=slave bundle=D port=gamma
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

	fm x_B[C][H][W];
	fm op_B[C][H][W];
	// int mean_B[C];
	// int var_B[C];
	// int CN_B;
	// int beta_B[C];
	// int gamma_B[C];

	for (int c=0; c<C; c++)
	{
		for (int h=0; h<H; h++)
		{
			for(int w=0; w<W; w++)
			{

				x_B[c][h][w] = x[c][h][w];
			}
		}
	}

//#pragma HLS pipeline off
////#pragma HLS unroll
//	for (int repli=0; repli<5; repli++)
//	{

	for (int c = 0; c < C; c+=1)
	{
		for (int h = 0; h < H; h++)
		{
// #pragma HLS pipeline
			for (int w = 0; w < W; w++)
			{
				// for (int ww=0; ww < 4; ww++)
					op_B[c][h][w] = (x_B[c][h][w] - mean[c]) / var[c] / CN * gamma[c] + beta[c];
				// op_B[c][h][w+ww] = (x_B[c][h][w+ww] - mean[c]) / var[c] / CN * gamma[c] + beta[c];

			}
		}
	}
//	}

	for (int c = 0; c < C; c++)
	{
		for (int h = 0; h < H; h++)
		{
			for (int w = 0; w < W; w++)
			{
				op[c][h][w] = op_B[c][h][w];
			}

		}

	}

    return;
}





