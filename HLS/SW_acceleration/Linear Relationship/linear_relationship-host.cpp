#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <CL/cl2.hpp>

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
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

//OCL_CHECK doesn't work if call has templatized function call
#define OCL_CHECK(error,call)                                        \
    call;                                                            \
    if (error != CL_SUCCESS) {                                       \
      std::cout << __FILE__ << ": " << __LINE__ << " Error calling " \
      #call ", error code is: " << error << std::endl;               \
      exit(EXIT_FAILURE);                                            \
    }


#define DATA_SIZE (1024*1024)

int main(int argc, char* argv[]) {

    //TARGET_DEVICE macro needs to be passed from gcc command line
    if(argc != 2) {
		std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
		return EXIT_FAILURE;
	}

    char* xclbinFilename = argv[1];

    // Compute the size of array in bytes
    size_t size_in_bytes = DATA_SIZE * sizeof(float);

    std::vector<cl::Device> devices;
    cl::Device device;
    std::vector<cl::Platform> platforms;
    bool found_device = false;
    cl_int err;

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

    OCL_CHECK(err, cl::CommandQueue queue(context, device, cl::QueueProperties::Profiling, &err));

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


    cl::Kernel krnl_linear_relationship;
    OCL_CHECK(err, krnl_linear_relationship = cl::Kernel(program,"linear_relationship_kernel", &err));


    cl::Buffer buffer_A;
    cl::Buffer buffer_B;
    cl::Buffer buffer_C;

    OCL_CHECK(err, buffer_A = cl::Buffer(context, CL_MEM_READ_ONLY, size_in_bytes, nullptr, &err));
    OCL_CHECK(err, buffer_B = cl::Buffer(context, CL_MEM_READ_ONLY, size_in_bytes, nullptr, &err));
    OCL_CHECK(err, buffer_C = cl::Buffer(context, CL_MEM_WRITE_ONLY, size_in_bytes, nullptr, &err));

    float alpha = 1.34;
    float beta  = 2.45;
    float gamma = 3.45;



    //set the kernel Arguments
    int narg=0;
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,buffer_A));
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,buffer_B));
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,buffer_C));
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,alpha));
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,beta));
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,gamma));
    OCL_CHECK(err, err = krnl_linear_relationship.setArg(narg++,DATA_SIZE));


    //We then need to map our OpenCL buffers to get the pointers
    float *ptr_A = (float *) queue.enqueueMapBuffer (buffer_A , CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes);
    float *ptr_B = (float *) queue.enqueueMapBuffer (buffer_B , CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes);
    float *ptr_C = (float *) queue.enqueueMapBuffer (buffer_C , CL_TRUE , CL_MAP_READ , 0, size_in_bytes);


    //setting input data
    for(int i = 0 ; i< DATA_SIZE; i++){
	    ptr_A[i] = rand()/(1.0*RAND_MAX);
	    ptr_B[i] = rand()/(1.0*RAND_MAX);
    }

    hardware_start = getTimestamp();

    OCL_CHECK(err, err = queue.enqueueMigrateMemObjects({buffer_A,buffer_B},0/* 0 means from host*/));
    OCL_CHECK(err, err = queue.enqueueTask(krnl_linear_relationship));
    OCL_CHECK(err, err = queue.enqueueMigrateMemObjects({buffer_C},CL_MIGRATE_MEM_OBJECT_HOST));
    OCL_CHECK(err, err = queue.finish());

    hardware_end = getTimestamp();
    hardware_time = (hardware_end-hardware_start)/1000;
	std::cout << "Exeution time running running kernel in hardware 1: "
        		    << hardware_time << " msec " << std::endl;


    //Verify the result
    int match = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        float host_result = alpha*ptr_A[i] + beta*ptr_B[i]+gamma;
        double diff = fabs(ptr_C[i]-host_result);
        if(diff > 0.0001 || diff != diff){
            std::cout << "Error at " << i
            		  << " C hardware is " << ptr_C[i]
					  << " but C golden is " << host_result
					  << std::endl;
            match = 1;
            break;
        }
    }

    OCL_CHECK(err, err = queue.enqueueUnmapMemObject(buffer_A , ptr_A));
    OCL_CHECK(err, err = queue.enqueueUnmapMemObject(buffer_B , ptr_B));
    OCL_CHECK(err, err = queue.enqueueUnmapMemObject(buffer_C , ptr_C));
    OCL_CHECK(err, err = queue.finish());

    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl;
    return (match ? EXIT_FAILURE :  EXIT_SUCCESS);



}
