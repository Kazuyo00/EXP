#include <CL/cl.h>
#include <cstdio>
#include <fstream>
#include <iosfwd>
#include <string>
#include <vector>
#include <iostream>

//=======================

//#include "xcl2.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>

//=======================

using std::ifstream;
using std::streamsize;
using std::string;
using std::vector;
using std::ios;

//==============================

#define HEI 128
#define WID 128

static const std::string error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %d Device result = %d\n";

float I[HEI*WID], II[HEI*WID];

double gettimeofday_sec()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}
//==============================

#define ERROR_CASE(err) \
    case err:           \
        return #err;    \
        break

const char *error_string(cl_int error_code) {
    switch (error_code) {
        ERROR_CASE(CL_SUCCESS);
        ERROR_CASE(CL_DEVICE_NOT_FOUND);
        ERROR_CASE(CL_DEVICE_NOT_AVAILABLE);
        ERROR_CASE(CL_COMPILER_NOT_AVAILABLE);
        ERROR_CASE(CL_MEM_OBJECT_ALLOCATION_FAILURE);
        ERROR_CASE(CL_OUT_OF_RESOURCES);
        ERROR_CASE(CL_OUT_OF_HOST_MEMORY);
        ERROR_CASE(CL_PROFILING_INFO_NOT_AVAILABLE);
        ERROR_CASE(CL_MEM_COPY_OVERLAP);
        ERROR_CASE(CL_IMAGE_FORMAT_MISMATCH);
        ERROR_CASE(CL_IMAGE_FORMAT_NOT_SUPPORTED);
        ERROR_CASE(CL_BUILD_PROGRAM_FAILURE);
        ERROR_CASE(CL_MAP_FAILURE);
        ERROR_CASE(CL_INVALID_VALUE);
        ERROR_CASE(CL_INVALID_DEVICE_TYPE);
        ERROR_CASE(CL_INVALID_PLATFORM);
        ERROR_CASE(CL_INVALID_DEVICE);
        ERROR_CASE(CL_INVALID_CONTEXT);
        ERROR_CASE(CL_INVALID_QUEUE_PROPERTIES);
        ERROR_CASE(CL_INVALID_COMMAND_QUEUE);
        ERROR_CASE(CL_INVALID_HOST_PTR);
        ERROR_CASE(CL_INVALID_MEM_OBJECT);
        ERROR_CASE(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR);
        ERROR_CASE(CL_INVALID_IMAGE_SIZE);
        ERROR_CASE(CL_INVALID_SAMPLER);
        ERROR_CASE(CL_INVALID_BINARY);
        ERROR_CASE(CL_INVALID_BUILD_OPTIONS);
        ERROR_CASE(CL_INVALID_PROGRAM);
        ERROR_CASE(CL_INVALID_PROGRAM_EXECUTABLE);
        ERROR_CASE(CL_INVALID_KERNEL_NAME);
        ERROR_CASE(CL_INVALID_KERNEL_DEFINITION);
        ERROR_CASE(CL_INVALID_KERNEL);
        ERROR_CASE(CL_INVALID_ARG_INDEX);
        ERROR_CASE(CL_INVALID_ARG_VALUE);
        ERROR_CASE(CL_INVALID_ARG_SIZE);
        ERROR_CASE(CL_INVALID_KERNEL_ARGS);
        ERROR_CASE(CL_INVALID_WORK_DIMENSION);
        ERROR_CASE(CL_INVALID_WORK_GROUP_SIZE);
        ERROR_CASE(CL_INVALID_WORK_ITEM_SIZE);
        ERROR_CASE(CL_INVALID_GLOBAL_OFFSET);
        ERROR_CASE(CL_INVALID_EVENT_WAIT_LIST);
        ERROR_CASE(CL_INVALID_EVENT);
        ERROR_CASE(CL_INVALID_OPERATION);
        ERROR_CASE(CL_INVALID_GL_OBJECT);
        ERROR_CASE(CL_INVALID_BUFFER_SIZE);
        ERROR_CASE(CL_INVALID_MIP_LEVEL);
        ERROR_CASE(CL_INVALID_GLOBAL_WORK_SIZE);
        ERROR_CASE(CL_COMPILE_PROGRAM_FAILURE);
        ERROR_CASE(CL_LINKER_NOT_AVAILABLE);
        ERROR_CASE(CL_LINK_PROGRAM_FAILURE);
        ERROR_CASE(CL_DEVICE_PARTITION_FAILED);
        ERROR_CASE(CL_KERNEL_ARG_INFO_NOT_AVAILABLE);
        ERROR_CASE(CL_INVALID_PROPERTY);
        ERROR_CASE(CL_INVALID_IMAGE_DESCRIPTOR);
        ERROR_CASE(CL_INVALID_COMPILER_OPTIONS);
        ERROR_CASE(CL_INVALID_LINKER_OPTIONS);
        ERROR_CASE(CL_INVALID_DEVICE_PARTITION_COUNT);
        default:
            printf("Unknown OpenCL Error (%d)\n", error_code);
            break;
    }
    return nullptr;
}

//xcl2.hppの代わりにこのようにバイナリファイルを読み込む必要がある。
vector<unsigned char> readBinary(const std::string &fileName) {
    ifstream file(fileName, ios::binary | ios::ate);
    if (file) {
        file.seekg(0, ios::end);
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);
        vector<unsigned char> buffer(size);
        file.read((char *)buffer.data(), size);
        return buffer;
    } else {
        fprintf(stderr, "%s not found\n", fileName.c_str());
        exit(-1);
    }
    return std::vector<unsigned char>(0);
}


int main(int argc, char **argv)
{

	int i, j, p[HEI][WID + 1];

	size_t mem_size = sizeof(float)*HEI*WID;

	double	start, end;

	FILE *fp;

	fp = fopen("/home/omori/workspace/20180630.asc", "r");
	if (fp == NULL)
	{
		printf("no such file\n");
		exit(1);
	}


  for (i = 0; i < HEI; i++)
  {
      for (j = 0; j <= WID; j++)
      {
        fscanf(fp, "%d", &p[i][j]);
      }
  }


  for (i = 0; i < HEI; i++)
  {
      for (j = 0; j < WID; j++)
      {
        I[i*WID + j] = (float)p[i][j + 1];
      }
  }

	printf("I[0] = %lf\n", I[0]);
  printf("I[129] = %lf\n", I[129]);




		if (argc != 2) {
			printf("Usage: %s "
					"./xclbin/vector_addition.<emulation_mode>.<dsa>.xclbin\n",
					argv[0]);
			return EXIT_FAILURE;
		}
	  //static const int elements = 128;
	  char *binary_file_path = argv[1];

	  // Error handling in OpenCL is performed using the cl_int specifier. OpenCL
	  // functions either return or accept pointers to cl_int types to indicate if
	  // an error occured.
	  cl_int err;
	  cl_event calculation;
	  cl_uint num_platforms;
	  if ((err = clGetPlatformIDs(0, nullptr, &num_platforms))) {
	      printf(
	          "Fatal Error calling clGetPlatformIDs: %s\n"
	          "This can be caused by an invalid installation of the OpenCL "
	          "runtime. Please make sure the installation was successful.\n",
	          error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  if (num_platforms == 0) {
	      printf(
	          "No platforms were found. This could be caused because the OpenCL "
	          "icd was not installed in the /etc/OpenCL/vendors directory.\n");
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  vector<cl_platform_id> platforms(num_platforms + 1);
	  if ((err = clGetPlatformIDs(num_platforms, platforms.data(), nullptr))) {
	      printf("Error: Failed to find an OpenCL platform!\n");
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  string platform_name(1024, '\0');
	  size_t actual_size = 0;
	  if ((err = clGetPlatformInfo(platforms[0], CL_PLATFORM_NAME,
	                               platform_name.size(),
	                               (void *)platform_name.data(), &actual_size))) {
	      printf("Error: Could not determine platform name!\n");
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }
	  printf("Platform Name: %s\n", platform_name.c_str());

	  if ((err = clGetPlatformInfo(platforms[0], CL_PLATFORM_VERSION,
	                               platform_name.size(),
	                               (void *)platform_name.data(), &actual_size))) {
	      printf("Error: Could not determine platform OpenCL Version!\n");
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }
	  printf("Platform Name: %s\n", platform_name.c_str());

	  cl_device_id device_id = 0;
	  if ((err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 1, &device_id,
	                            nullptr))) {
	      printf(
	          "Fatal Error calling clGetDeviceIDs: %s\n"
	          "Unexpected error getting device IDs. This may happen if you are "
	          "Targeting hardware or software emulation and the "
	          "XCL_EMULATION_MODE environment variable is not set. Also makeyou "
	          "have set the you have run the emconfigutil to setup the emulation "
	          "environment.\n\n",
	          error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  cl_context_properties props[3] = {CL_CONTEXT_PLATFORM,
	                                    (cl_context_properties)platforms[0], 0};
	  // clCreate* function calls return the object so they return error codes
	  // using
	  // pointers to cl_int as their last parameters

	  cl_context context = clCreateContext(props, 1, &device_id, nullptr, nullptr, &err);

	  cl_command_queue command_queue = clCreateCommandQueue(
	      context, device_id, CL_QUEUE_PROFILING_ENABLE, &err);

	  if (err) {
	      printf(
	          "Fatal Error calling clCreateCommandQueue: %s\n"
	          "Unexpected error creating a command queue.\n\n",
	          error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  // Loading the file
	  vector<unsigned char> binary = readBinary(binary_file_path);
	  size_t binary_size = binary.size();
	  const unsigned char *binary_data = binary.data();

	  cl_program program = clCreateProgramWithBinary(context, 1, &device_id, &binary_size,
	                                      &binary_data, NULL, &err);
	  if (err) {
	      printf(
	          "Fatal Error calling clCreateProgramWithBinary: %s\n"
	          "Unexpected error creating a program from binary. Make sure you "
	          "executed this program with the correct path to the binary.\n\n",
	          error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  cl_kernel kernel = clCreateKernel(program, "exp_cal", &err);

	  if (err) {
	      printf(
	          "Fatal Error calling clCreateKernel: %s\n"
	          "Unexpected error when creating kernel. Make sure you passed the "
	          "correct binary into the executable of this program.\n\n",
	          error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	///////////////////////////////////////////////////////////////////////////

	 /* cl_mem clCreateBuffer(cl_context context,//OpenCLのコンテキストを指定
	  							cl_mem_flags flags,//フラグ
	  							size_t size, //確保するメモリのバイトサイズ
	  							void *host_ptr,//CPU側のデータへのポインタ
	  							cl_int *errcode_ret)//エラーコードを拾う時に使用 */

	  cl_mem d_I = clCreateBuffer(context, CL_MEM_READ_ONLY, mem_size, nullptr, &err);
	  if (err) {
	      printf("Fatal Error calling clCreateBuffer: %s\n", error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  cl_mem d_II = clCreateBuffer(context, CL_MEM_READ_WRITE, mem_size, nullptr, &err);
	  if (err) {
	      printf("Fatal Error calling clCreateBuffer: %s\n", error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	///////////////////////////////////////////////////////////////////////////

	//CPU ⇒ Kernel Device のデータ転送
	 /*clEnqueueWriteBuffer 			(	cl_command_queue  //command_queue、
	   										cl_mem  //バッファ、
	   										cl_bool  //blocking_write、
	   										size_t  //オフセット、
	   										size_t  //cb、
	   										const void  //ptr、
	   										cl_uint  //num_events_in_wait_list、
	   										const cl_event  //event_wait_list、
	   										cl_event  //イベント)*/

	  if ((err = clEnqueueWriteBuffer(command_queue, d_I, CL_TRUE, 0, mem_size,
			  I, 0, nullptr, nullptr))) {
	      printf("Fatal Error calling clEnqueueWriteBuffer: %s\n",
	             error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	///////////////////////////////////////////////////////////////////////////

	  if ((err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&d_I))) {
	      printf("Fatal Error calling clSetKernelArg: %s\n", error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	  if ((err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&d_II))) {
	      printf("Fatal Error calling clSetKernelArg: %s\n", error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  }

	///////////////////////////////////////////////////////////////////////////

		size_t global[2];
		size_t local[2];

		global[0] = HEI;
		global[1] = WID;
		local[0] = 128;
		local[1] = 128;

		start = gettimeofday_sec();
		//NDrangeの設定
		if ((err = clEnqueueNDRangeKernel(command_queue,
				  	  	  	  	  	  	  	  	  kernel,
												  2, //ワークグループ内のグローバルワークアイテムとワークアイテムを指定,次元の数。0~3
												  nullptr, //global_work_offset nullでいい。
												  global, //global_work_size
												  local, //local_work_size
												  0, //event_wait_list
												  nullptr, //event
												  &calculation)))
		{
		      printf("Fatal Error calling clEnqueueNDRangeKernel: %s\n",
		             error_string(err));
		      printf("TEST FAILED\n");
		      exit(EXIT_FAILURE);
		}
		//
		//計算終了を待つため(同期を取るため)
		clWaitForEvents(1,&calculation);
		//clFinish(&calculation);
		end = gettimeofday_sec();
		printf("clEnqueueNDRangeKernel TIME = %lf[ms]\n",1000*(end-start));

		start = gettimeofday_sec();

///////////////////////////////////////////////////////////////////////////

	  //Kernel Device ⇒ CPU のデータ転送
	  /*clEnqueueReadBuffer(cl_command_queue command_queue,//コマンドキュー
	  	  	  	  	  	  	  cl_mem buffer,//バッファオブジェクト
	  	  	  	  	  	  	  cl_bool blocking_read,//ブロッキングモードを指定(CL_TRUE or CL_FALSE)
	  	  	  	  	  	  	  size_t offset,//データの開始位置のオフセット
	  	  	  	  	  	  	  size_t cb,//データのバイトサイズ
	  	  	  	  	  	  	  void *ptr,//読み出し先。CPU側の格納用配列データのアドレス
	  	  	  	  	  	  	  cl_uint num_events_in_wait_list,//イベントのリスト。とりあえず「0」でいい
	  	  	  	  	  	  	  const cl_event *event_wait_list,//イベントリストの数。とりあえず「NULL」でいい
	  	  	  	  	  	  	  cl_event *event)//とりあえずNULLでいい*/

	  if ((err = clEnqueueReadBuffer(command_queue, d_II, CL_TRUE, 0, mem_size,
										  II, 0, nullptr, nullptr)))
	  	  {
	      printf("Fatal Error calling clEnqueueWriteBuffer: %s\n",
	             error_string(err));
	      printf("TEST FAILED\n");
	      exit(EXIT_FAILURE);
	  	  }

 ///////////////////////////////////////////////////////////////////////////

	  end = gettimeofday_sec();

	  printf("clEnqueueReadBuffer TIME = %lf[ms]\n\n",1000*(end-start));

	  printf("II[0] = %lf\n", II[0]);
	  printf("II[129] = %lf\n", II[129]);


		clReleaseDevice(device_id);
		clReleaseMemObject(d_I);
		clReleaseMemObject(d_II);
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(command_queue);
		clReleaseContext(context);
		clReleaseEvent(calculation);


	fclose(fp);
	return 0;
}

