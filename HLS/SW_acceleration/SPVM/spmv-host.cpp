#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "spmv.h"
#include <math.h>

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <CL/cl2.hpp>


#include <sys/time.h>
#include <time.h>

double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}

double hardware_start;
double hardware_end;
double hardware_time;


double software_start;
double software_end;
double software_time;



int main(int argc, char* argv[]) {


	char          inFilename[1000];
	unsigned int  n;
	unsigned int  m;
	unsigned int  nnz;




	strcpy(inFilename, "data/TSC_OPF_1047.mtx.csr");
	spm_get_size(inFilename, n, m, nnz);


	if(argc != 2) {
		std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
		return EXIT_FAILURE;
	}

	char* xclbinFilename = argv[1];

    std::vector<cl::Device> devices;
    cl::Device device;
    std::vector<cl::Platform> platforms;
    bool found_device = false;
    cl_int err;
    //traversing all Platforms To find Xilinx Platform and targeted
    //Device in Xilinx Platform
    OCL_CHECK(err, err = cl::Platform::get(&platforms));

    for(size_t i = 0; (i < platforms.size() ) & (found_device == false) ;i++){
        cl::Platform platform = platforms[i];
        OCL_CHECK(err, std::string platformName = platform.getInfo<CL_PLATFORM_NAME>(&err));
        if ( platformName == "Xilinx"){
            devices.clear();
            OCL_CHECK(err, err = platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices));
	    if (devices.size()){
		    device = devices[0];
		    found_device = true;
		    break;
	    }
        }
    }
    if (found_device == false){
       std::cout << "Error: Unable to find Target Device "
           << device.getInfo<CL_DEVICE_NAME>() << std::endl;
       return EXIT_FAILURE;
    }


    OCL_CHECK(err, cl::Context context(device, NULL, NULL, NULL, &err));
    OCL_CHECK(err, cl::CommandQueue queue(context, device, cl::QueueProperties::Profiling | cl::QueueProperties::OutOfOrder, &err));


    // Load xclbin
    std::cout << "Loading: '" << xclbinFilename << "'\n";
    std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
    bin_file.seekg (0, bin_file.end);
    unsigned nb = bin_file.tellg();
    bin_file.seekg (0, bin_file.beg);
    char *buf = new char [nb];
    bin_file.read(buf, nb);

    // Creating Program from Binary File
    cl::Program::Binaries bins;
    bins.push_back({buf,nb});
    devices.resize(1);
    OCL_CHECK(err, cl::Program program(context, devices, bins, NULL, &err));

    cl::Kernel krnl_spmv;
    OCL_CHECK(err, krnl_spmv = cl::Kernel(program,"spmv_kernel", &err));


    cl::Buffer buffer_values;
    cl::Buffer buffer_col_indices;
    cl::Buffer buffer_row_indices;
    cl::Buffer buffer_x;
    cl::Buffer buffer_y;

    OCL_CHECK(err, buffer_values = cl::Buffer(context, CL_MEM_READ_ONLY, nnz*sizeof(float), nullptr, &err));
    OCL_CHECK(err, buffer_col_indices = cl::Buffer(context, CL_MEM_READ_ONLY, nnz*sizeof(unsigned int), nullptr, &err));
    OCL_CHECK(err, buffer_row_indices = cl::Buffer(context, CL_MEM_READ_ONLY, (n+1)*sizeof(unsigned int), nullptr, &err));
    OCL_CHECK(err, buffer_x = cl::Buffer(context, CL_MEM_READ_ONLY, m*sizeof(float), nullptr, &err));
    OCL_CHECK(err, buffer_y = cl::Buffer(context, CL_MEM_WRITE_ONLY, n*sizeof(float), nullptr, &err));


    int narg=0;
    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,buffer_values));

    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,buffer_col_indices));
    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,buffer_row_indices));
    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,buffer_x));
    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,buffer_y));
    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,n));
    OCL_CHECK(err, err = krnl_spmv.setArg(narg++,m));


    float *ptr_values = (float *) queue.enqueueMapBuffer (buffer_values , CL_TRUE , CL_MAP_WRITE , 0, nnz*sizeof(float));
    unsigned int *ptr_col_indices = (unsigned int *) queue.enqueueMapBuffer (buffer_col_indices , CL_TRUE , CL_MAP_WRITE , 0, nnz*sizeof(unsigned int));
    unsigned int *ptr_row_indices = (unsigned int *) queue.enqueueMapBuffer (buffer_row_indices , CL_TRUE , CL_MAP_WRITE , 0, (n+1)*sizeof(unsigned int));
    float *ptr_x = (float *) queue.enqueueMapBuffer (buffer_x , CL_TRUE , CL_MAP_WRITE , 0, m*sizeof(float));

    float *ptr_y = (float *) queue.enqueueMapBuffer (buffer_y , CL_TRUE , CL_MAP_READ , 0, n*sizeof(float));

    //setting input data
    read_mtx_spm( inFilename, ptr_values, ptr_col_indices, ptr_row_indices);
    for (unsigned int i = 0; i < m; i++) {
    	ptr_x[i] = rand()/RAND_MAX;
    }


    hardware_start = getTimestamp();
    OCL_CHECK(err, err = queue.enqueueMigrateMemObjects({buffer_values,buffer_col_indices, buffer_row_indices, buffer_x},0/* 0 means from host*/));
    OCL_CHECK(err, err = queue.enqueueTask(krnl_spmv));
    OCL_CHECK(err, err = queue.enqueueMigrateMemObjects({buffer_y},CL_MIGRATE_MEM_OBJECT_HOST));

    queue.finish();
    hardware_end = getTimestamp();
    hardware_time = (hardware_end-hardware_start)/1000;
	std::cout << "Exeution time running kernel in hardware: "
        		    << hardware_time << " msec " << std::endl;


    // GOLDEN model
	software_start = getTimestamp();
    unsigned int i=0, rowStart=0, rowEnd=n;
    float *y_sw = (float *)malloc(n*sizeof(float));
    float y0=0.0;
    for (i = rowStart; i < rowEnd; ++i) {
    	y0 = 0.0;
    	for (unsigned int j=ptr_row_indices[i]; j<ptr_row_indices[i+1]; j++) {
        	y0 += ptr_values[j] * ptr_x[ptr_col_indices[j]];
        }
        y_sw[i] = y0;
    }
    software_end = getTimestamp();
    software_time = (software_end-software_start)/1000;
	std::cout << "Exeution time running kernel in software 2: "
        		    << software_time << " msec " << std::endl;


    //Verify the result
    int match = 0;
    for (unsigned int i = 0; i < n; i++) {
		float diff = fabs(y_sw[i]-ptr_y[i]);
		if(diff > 0.0001 || diff != diff){
			std::cout << "error occurs at " << i
					  << " with value y_hw = " << ptr_y[i]
					  << ", should be y_sw = " << y_sw[i]
  					  << std::endl;
            match = 1;
            break;
        }
    }

    queue.enqueueUnmapMemObject(buffer_values , ptr_values);
    queue.enqueueUnmapMemObject(buffer_col_indices , ptr_col_indices);
    queue.enqueueUnmapMemObject(buffer_row_indices , ptr_row_indices);
    queue.enqueueUnmapMemObject(buffer_y , ptr_y);
    queue.finish();

    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl;
    return (match ? EXIT_FAILURE :  EXIT_SUCCESS);



}
