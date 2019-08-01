#include<math.h>

#define HEI 128
#define WID 128
#define PAGE 10

void exp_cal(float I[HEI*WID])
{
	int i, j;
	float II[HEI*WID];

	for (i = 0; i < HEI; i++){
#pragma HLS LOOP_FLATTEN
#pragma HLS LOOP_MERGE
#pragma HLS PIPELINE
	   for (j = 0; j < WID; j++){
		     II[i * WID + j] = I[i * WID + j];
	    }
	 }

	for (i = 0; i < HEI; i++){
	   for (j = 0; j < WID; j++){
#pragma HLS PIPELINE
		     II[i * WID + j] = expf((12657 - II[i * WID + j]) / 23546);
	    }
	 }

	for (i = 0; i < HEI; i++){
#pragma HLS LOOP_FLATTEN
#pragma HLS LOOP_MERGE
#pragma HLS PIPELINE
		for (j = 0; j < WID; j++){
			I[i * WID + j] = II[i * WID + j];
		}
	}

}
