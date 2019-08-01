#define HEI 128
#define WID 128
#define PAGE 1

__attribute__((reqd_work_group_size(128, 128, 1)))
//__attribute__((always_inline))
//__attribute__((xcl_dataflow))
__kernel void exp_cal(global float *I,
				global float *II)
{
	const int i = get_global_id(0);
	const int j = get_global_id(1);
	float q_I[HEI*WID] __attribute__((xcl_array_partition(complete, 1)));
	float q_II[HEI*WID] __attribute__((xcl_array_partition(complete, 1)));

	//__attribute__((opencl_unroll_hint))
	//__attribute__((xcl_pipeline_loop))
	__attribute__((xcl_pipeline_workitems))

		q_I[i * WID + j] = I[i * WID + j];


		q_II[i * WID + j] = half_exp(0.0010644 * q_I[i * WID + j]);


		II[i * WID + j] = q_II[i * WID + j];
}

