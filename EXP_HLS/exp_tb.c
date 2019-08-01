-#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define HEI 128
#define WID 128
#define PAGE 10

float I[HEI*WID];

int main()
{

	int i, j, k, p[HEI][WID + 1], q[HEI][WID];

	FILE *fp;

	fp = fopen("C:\\Users\\i-omori\\AppData\\Roaming\\Xilinx\\Vivado\\20180630.asc", "r");
	if (fp == NULL)
	{
		printf("no such file\n");
		exit(1);
	}
	for (k = 0; k < PAGE; k++)
	{

		for (i = 0; i < HEI; i++)
		{
			for (j = 0; j <= WID; j++)
			{
				fscanf(fp, "%d", &p[i][j]);
			}
		}
		for (i = 0; i < HEI; i++)
		{
			for (j = 1; j <= WID; j++)
			{
				q[i][j - 1] = p[i][j];
			}
		}
		for (i = 0; i < HEI; i++)
		{
			for (j = 0; j < WID; j++)
			{
				I[i*WID + j] = (float)q[i][j];
			}
		}

    exp_cal(I);
    printf("I[0]=%f\n",I[0]);

  }

	fclose(fp);
	return 0;
}
