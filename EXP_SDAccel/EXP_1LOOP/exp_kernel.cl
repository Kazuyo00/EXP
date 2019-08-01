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
q_II[i * WID + 0] = exp(0.0010644 * q_I[i * WID + 0]);
q_II[i * WID + 1] = exp(0.0010644 * q_I[i * WID + 1]);
q_II[i * WID + 2] = exp(0.0010644 * q_I[i * WID + 2]);
q_II[i * WID + 3] = exp(0.0010644 * q_I[i * WID + 3]);
q_II[i * WID + 4] = exp(0.0010644 * q_I[i * WID + 4]);
q_II[i * WID + 5] = exp(0.0010644 * q_I[i * WID + 5]);
q_II[i * WID + 6] = exp(0.0010644 * q_I[i * WID + 6]);
q_II[i * WID + 7] = exp(0.0010644 * q_I[i * WID + 7]);
q_II[i * WID + 8] = exp(0.0010644 * q_I[i * WID + 8]);
q_II[i * WID + 9] = exp(0.0010644 * q_I[i * WID + 9]);
q_II[i * WID + 10] = exp(0.0010644 * q_I[i * WID + 10]);
q_II[i * WID + 11] = exp(0.0010644 * q_I[i * WID + 11]);
q_II[i * WID + 12] = exp(0.0010644 * q_I[i * WID + 12]);
q_II[i * WID + 13] = exp(0.0010644 * q_I[i * WID + 13]);
q_II[i * WID + 14] = exp(0.0010644 * q_I[i * WID + 14]);
q_II[i * WID + 15] = exp(0.0010644 * q_I[i * WID + 15]);
q_II[i * WID + 16] = exp(0.0010644 * q_I[i * WID + 16]);
q_II[i * WID + 17] = exp(0.0010644 * q_I[i * WID + 17]);
q_II[i * WID + 18] = exp(0.0010644 * q_I[i * WID + 18]);
q_II[i * WID + 19] = exp(0.0010644 * q_I[i * WID + 19]);
q_II[i * WID + 20] = exp(0.0010644 * q_I[i * WID + 20]);
q_II[i * WID + 21] = exp(0.0010644 * q_I[i * WID + 21]);
q_II[i * WID + 22] = exp(0.0010644 * q_I[i * WID + 22]);
q_II[i * WID + 23] = exp(0.0010644 * q_I[i * WID + 23]);
q_II[i * WID + 24] = exp(0.0010644 * q_I[i * WID + 24]);
q_II[i * WID + 25] = exp(0.0010644 * q_I[i * WID + 25]);
q_II[i * WID + 26] = exp(0.0010644 * q_I[i * WID + 26]);
q_II[i * WID + 27] = exp(0.0010644 * q_I[i * WID + 27]);
q_II[i * WID + 28] = exp(0.0010644 * q_I[i * WID + 28]);
q_II[i * WID + 29] = exp(0.0010644 * q_I[i * WID + 29]);
q_II[i * WID + 30] = exp(0.0010644 * q_I[i * WID + 30]);
q_II[i * WID + 31] = exp(0.0010644 * q_I[i * WID + 31]);
q_II[i * WID + 32] = exp(0.0010644 * q_I[i * WID + 32]);
q_II[i * WID + 33] = exp(0.0010644 * q_I[i * WID + 33]);
q_II[i * WID + 34] = exp(0.0010644 * q_I[i * WID + 34]);
q_II[i * WID + 35] = exp(0.0010644 * q_I[i * WID + 35]);
q_II[i * WID + 36] = exp(0.0010644 * q_I[i * WID + 36]);
q_II[i * WID + 37] = exp(0.0010644 * q_I[i * WID + 37]);
q_II[i * WID + 38] = exp(0.0010644 * q_I[i * WID + 38]);
q_II[i * WID + 39] = exp(0.0010644 * q_I[i * WID + 39]);
q_II[i * WID + 40] = exp(0.0010644 * q_I[i * WID + 40]);
q_II[i * WID + 41] = exp(0.0010644 * q_I[i * WID + 41]);
q_II[i * WID + 42] = exp(0.0010644 * q_I[i * WID + 42]);
q_II[i * WID + 43] = exp(0.0010644 * q_I[i * WID + 43]);
q_II[i * WID + 44] = exp(0.0010644 * q_I[i * WID + 44]);
q_II[i * WID + 45] = exp(0.0010644 * q_I[i * WID + 45]);
q_II[i * WID + 46] = exp(0.0010644 * q_I[i * WID + 46]);
q_II[i * WID + 47] = exp(0.0010644 * q_I[i * WID + 47]);
q_II[i * WID + 48] = exp(0.0010644 * q_I[i * WID + 48]);
q_II[i * WID + 49] = exp(0.0010644 * q_I[i * WID + 49]);
q_II[i * WID + 50] = exp(0.0010644 * q_I[i * WID + 50]);
q_II[i * WID + 51] = exp(0.0010644 * q_I[i * WID + 51]);
q_II[i * WID + 52] = exp(0.0010644 * q_I[i * WID + 52]);
q_II[i * WID + 53] = exp(0.0010644 * q_I[i * WID + 53]);
q_II[i * WID + 54] = exp(0.0010644 * q_I[i * WID + 54]);
q_II[i * WID + 55] = exp(0.0010644 * q_I[i * WID + 55]);
q_II[i * WID + 56] = exp(0.0010644 * q_I[i * WID + 56]);
q_II[i * WID + 57] = exp(0.0010644 * q_I[i * WID + 57]);
q_II[i * WID + 58] = exp(0.0010644 * q_I[i * WID + 58]);
q_II[i * WID + 59] = exp(0.0010644 * q_I[i * WID + 59]);
q_II[i * WID + 60] = exp(0.0010644 * q_I[i * WID + 60]);
q_II[i * WID + 61] = exp(0.0010644 * q_I[i * WID + 61]);
q_II[i * WID + 62] = exp(0.0010644 * q_I[i * WID + 62]);
q_II[i * WID + 63] = exp(0.0010644 * q_I[i * WID + 63]);
q_II[i * WID + 64] = exp(0.0010644 * q_I[i * WID + 64]);
q_II[i * WID + 65] = exp(0.0010644 * q_I[i * WID + 65]);
q_II[i * WID + 66] = exp(0.0010644 * q_I[i * WID + 66]);
q_II[i * WID + 67] = exp(0.0010644 * q_I[i * WID + 67]);
q_II[i * WID + 68] = exp(0.0010644 * q_I[i * WID + 68]);
q_II[i * WID + 69] = exp(0.0010644 * q_I[i * WID + 69]);
q_II[i * WID + 70] = exp(0.0010644 * q_I[i * WID + 70]);
q_II[i * WID + 71] = exp(0.0010644 * q_I[i * WID + 71]);
q_II[i * WID + 72] = exp(0.0010644 * q_I[i * WID + 72]);
q_II[i * WID + 73] = exp(0.0010644 * q_I[i * WID + 73]);
q_II[i * WID + 74] = exp(0.0010644 * q_I[i * WID + 74]);
q_II[i * WID + 75] = exp(0.0010644 * q_I[i * WID + 75]);
q_II[i * WID + 76] = exp(0.0010644 * q_I[i * WID + 76]);
q_II[i * WID + 77] = exp(0.0010644 * q_I[i * WID + 77]);
q_II[i * WID + 78] = exp(0.0010644 * q_I[i * WID + 78]);
q_II[i * WID + 79] = exp(0.0010644 * q_I[i * WID + 79]);
q_II[i * WID + 80] = exp(0.0010644 * q_I[i * WID + 80]);
q_II[i * WID + 81] = exp(0.0010644 * q_I[i * WID + 81]);
q_II[i * WID + 82] = exp(0.0010644 * q_I[i * WID + 82]);
q_II[i * WID + 83] = exp(0.0010644 * q_I[i * WID + 83]);
q_II[i * WID + 84] = exp(0.0010644 * q_I[i * WID + 84]);
q_II[i * WID + 85] = exp(0.0010644 * q_I[i * WID + 85]);
q_II[i * WID + 86] = exp(0.0010644 * q_I[i * WID + 86]);
q_II[i * WID + 87] = exp(0.0010644 * q_I[i * WID + 87]);
q_II[i * WID + 88] = exp(0.0010644 * q_I[i * WID + 88]);
q_II[i * WID + 89] = exp(0.0010644 * q_I[i * WID + 89]);
q_II[i * WID + 90] = exp(0.0010644 * q_I[i * WID + 90]);
q_II[i * WID + 91] = exp(0.0010644 * q_I[i * WID + 91]);
q_II[i * WID + 92] = exp(0.0010644 * q_I[i * WID + 92]);
q_II[i * WID + 93] = exp(0.0010644 * q_I[i * WID + 93]);
q_II[i * WID + 94] = exp(0.0010644 * q_I[i * WID + 94]);
q_II[i * WID + 95] = exp(0.0010644 * q_I[i * WID + 95]);
q_II[i * WID + 96] = exp(0.0010644 * q_I[i * WID + 96]);
q_II[i * WID + 97] = exp(0.0010644 * q_I[i * WID + 97]);
q_II[i * WID + 98] = exp(0.0010644 * q_I[i * WID + 98]);
q_II[i * WID + 99] = exp(0.0010644 * q_I[i * WID + 99]);
q_II[i * WID + 100] = exp(0.0010644 * q_I[i * WID + 100]);
q_II[i * WID + 101] = exp(0.0010644 * q_I[i * WID + 101]);
q_II[i * WID + 102] = exp(0.0010644 * q_I[i * WID + 102]);
q_II[i * WID + 103] = exp(0.0010644 * q_I[i * WID + 103]);
q_II[i * WID + 104] = exp(0.0010644 * q_I[i * WID + 104]);
q_II[i * WID + 105] = exp(0.0010644 * q_I[i * WID + 105]);
q_II[i * WID + 106] = exp(0.0010644 * q_I[i * WID + 106]);
q_II[i * WID + 107] = exp(0.0010644 * q_I[i * WID + 107]);
q_II[i * WID + 108] = exp(0.0010644 * q_I[i * WID + 108]);
q_II[i * WID + 109] = exp(0.0010644 * q_I[i * WID + 109]);
q_II[i * WID + 110] = exp(0.0010644 * q_I[i * WID + 110]);
q_II[i * WID + 111] = exp(0.0010644 * q_I[i * WID + 111]);
q_II[i * WID + 112] = exp(0.0010644 * q_I[i * WID + 112]);
q_II[i * WID + 113] = exp(0.0010644 * q_I[i * WID + 113]);
q_II[i * WID + 114] = exp(0.0010644 * q_I[i * WID + 114]);
q_II[i * WID + 115] = exp(0.0010644 * q_I[i * WID + 115]);
q_II[i * WID + 116] = exp(0.0010644 * q_I[i * WID + 116]);
q_II[i * WID + 117] = exp(0.0010644 * q_I[i * WID + 117]);
q_II[i * WID + 118] = exp(0.0010644 * q_I[i * WID + 118]);
q_II[i * WID + 119] = exp(0.0010644 * q_I[i * WID + 119]);
q_II[i * WID + 120] = exp(0.0010644 * q_I[i * WID + 120]);
q_II[i * WID + 121] = exp(0.0010644 * q_I[i * WID + 121]);
q_II[i * WID + 122] = exp(0.0010644 * q_I[i * WID + 122]);
q_II[i * WID + 123] = exp(0.0010644 * q_I[i * WID + 123]);
q_II[i * WID + 124] = exp(0.0010644 * q_I[i * WID + 124]);
q_II[i * WID + 125] = exp(0.0010644 * q_I[i * WID + 125]);
q_II[i * WID + 126] = exp(0.0010644 * q_I[i * WID + 126]);
q_II[i * WID + 127] = exp(0.0010644 * q_I[i * WID + 127]);

		}

		for (i = 0; i < HEI; i++){
			for (j = 0; j < WID; j++){
				II[i * WID + j] = q_II[i * WID + j];
			}
		}
}
