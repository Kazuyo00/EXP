#define HEI 128
#define WID 128
#define PAGE 1

kernel __attribute__((reqd_work_group_size(1, 1, 1)))
__kernel void exp_cal(global float *I,
				global float *II)
{
	int i, j, n;
	float q_I[HEI*WID]; //__attribute__((xcl_array_partition(complete, 1)));
	float q_II[HEI*WID];


	//__attribute__((opencl_unroll_hint))
	//__attribute__((xcl_pipeline_loop))

		for (i = 0; i < HEI; i++){
			for (j = 0; j < WID; j++){
				q_I[i * WID + j] = I[i * WID + j];
			}
		}

		for (i = 0; i < HEI; i++){
			for (j = 0; j < WID; j++){
				q_II[i * WID + j] = exp(0.0010644 * q_I[i * WID + j]);
			}
		}

		for (i = 0; i < HEI; i++){
			for (j = 0; j < WID; j++){
				II[i * WID + j] = q_II[i * WID + j];
			}
		}
}
