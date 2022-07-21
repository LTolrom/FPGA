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

double getTimestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}

double hardware_start;
double hardware_end;
double hardware_time;


int main(int argc, char* argv[]) {


	unsigned int n =  512;
	unsigned int m =  1024;
    if(argc != 2) {
		std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
		return EXIT_FAILURE;
	}

    char* xclbinFilename = argv[1];

    std::vector<cl::Device> devices;
    cl::Device device;
    std::vector<cl::Platform> platforms;
    bool found_device = false;

    //traversing all Platforms To find Xilinx Platform and targeted
    //Device in Xilinx Platform
    cl::Platform::get(&platforms);
    for(size_t i = 0; (i < platforms.size() ) & (found_device == false) ;i++){
        cl::Platform platform = platforms[i];
        std::string platformName = platform.getInfo<CL_PLATFORM_NAME>();
        if ( platformName == "Xilinx"){
            devices.clear();
            platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
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

    // Creating Context and Command Queue for selected device
    cl::Context context(device);
    cl::CommandQueue queue(context, device, CL_QUEUE_PROFILING_ENABLE);

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
    cl::Program program(context, devices, bins);

    cl::Kernel krnl_mxv(program,"mxv_kernel");

    cl::Buffer buffer_A(context,  CL_MEM_READ_ONLY,  n*m*sizeof(float));
    cl::Buffer buffer_x(context,  CL_MEM_READ_ONLY,  m*sizeof(float));
    cl::Buffer buffer_y(context,  CL_MEM_WRITE_ONLY, n*sizeof(float));


    //set the kernel Arguments
    int narg=0;
    krnl_mxv.setArg(narg++,buffer_A);
    krnl_mxv.setArg(narg++,buffer_x);
    krnl_mxv.setArg(narg++,buffer_y);
    krnl_mxv.setArg(narg++,n);
    krnl_mxv.setArg(narg++,m);

    float *ptr_A = (float *) queue.enqueueMapBuffer (buffer_A , CL_TRUE , CL_MAP_WRITE , 0, n*m*sizeof(float));
    float *ptr_x = (float *) queue.enqueueMapBuffer (buffer_x , CL_TRUE , CL_MAP_WRITE , 0, m*sizeof(float));
    float *ptr_y = (float *) queue.enqueueMapBuffer (buffer_y , CL_TRUE , CL_MAP_READ  , 0, n*sizeof(float));

    for (unsigned int i = 0; i < n*m; i++) {
    	ptr_A[i] = rand()/(1.0*RAND_MAX);
    }
    for (unsigned int i = 0; i < m; i++) {
    	ptr_x[i] = rand()/(1.0*RAND_MAX);
    }

    hardware_start = getTimestamp();

    queue.enqueueMigrateMemObjects({buffer_A, buffer_x},0/* 0 means from host*/);
    queue.enqueueTask(krnl_mxv);
    queue.enqueueMigrateMemObjects({buffer_y},CL_MIGRATE_MEM_OBJECT_HOST);
    queue.finish();

    hardware_end = getTimestamp();
    hardware_time = (hardware_end-hardware_start)/1000;
    std::cout << "Exeution time running mxv on FPGA: "
              << hardware_time << " msec " << std::endl;
    //--------------------------
    hardware_start = getTimestamp();

    queue.enqueueMigrateMemObjects({buffer_A, buffer_x},0/* 0 means from host*/);
    queue.finish();

    hardware_end = getTimestamp();
    hardware_time = (hardware_end-hardware_start)/1000;
    std::cout << "Exeution time running enqueueMigrateMemObjects to FPGA: "
              << hardware_time << " msec " << std::endl;
    //---------------------------------------
    hardware_start = getTimestamp();

    queue.enqueueTask(krnl_mxv);
    queue.finish();

    hardware_end = getTimestamp();
    hardware_time = (hardware_end-hardware_start)/1000;
    std::cout << "Exeution time running kernel on FPGA: "
              << hardware_time << " msec " << std::endl;
    //-----------------------------------------
    hardware_start = getTimestamp();

    queue.enqueueMigrateMemObjects({buffer_y},CL_MIGRATE_MEM_OBJECT_HOST);
    queue.finish();

    hardware_end = getTimestamp();
    hardware_time = (hardware_end-hardware_start)/1000;
    std::cout << "Exeution time running enqueueMigrateMemObjects from FPGA: "
              << hardware_time << " msec " << std::endl;

    //Verify the result
    float *y_sw = (float *)malloc(n*sizeof(float));
	for (unsigned int i = 0; i < n; i++) {
		y_sw[i] = 0;
		for (unsigned int j = 0; j < m; j++) {
			y_sw[i] += ptr_A[i*m+j]*ptr_x[j];
		}
	}



    int match = 0;
    for (unsigned int i = 0; i < n; i++) {
		float diff = fabs(y_sw[i]-ptr_y[i]);
		if(diff > 0.01 || diff != diff){
			std::cout << "error occurs at " << i
					  << " with value y_hw = " << ptr_y[i]
					  << ", should be y_sw = " << y_sw[i]
  					  << std::endl;
            match = 1;
            break;
        }
    }

    queue.enqueueUnmapMemObject(buffer_A , ptr_A);
    queue.enqueueUnmapMemObject(buffer_x , ptr_x);
    queue.enqueueUnmapMemObject(buffer_y , ptr_y);
    queue.finish();

    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl;
    return (match ? EXIT_FAILURE :  EXIT_SUCCESS);


}


