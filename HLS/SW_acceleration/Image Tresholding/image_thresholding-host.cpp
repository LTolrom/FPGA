#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <CL/cl2.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/videoio/videoio.hpp>

#include <stdlib.h>
#include <fstream>
#include <iostream>



using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  int status = 0;


  Mat src_image;
  Mat grey_image;
  src_image=imread("data/test_image.jpg");
  if (!src_image.data) {
    cout << "Could not open image" << endl;
    return 0;
  };

  unsigned int DATA_SIZE = src_image.rows * src_image.cols;
  size_t size_in_bytes = DATA_SIZE * sizeof(unsigned char);
  cvtColor(src_image, grey_image, cv::COLOR_BGR2GRAY);

  Mat dst, dst_golden;
  dst = grey_image.clone();
  dst_golden = grey_image.clone();
  unsigned int  threshold_value = 128;
  unsigned int max_binary_value = 255;

  std::cout << " size_in_bytes = '" << size_in_bytes << "'\n";

  if(argc != 2) {
  	std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
    return EXIT_FAILURE;
  }


  char* xclbinFilename = argv[1];
  std::vector<cl::Device> devices;
  cl::Device device;
  std::vector<cl::Platform> platforms;
  bool found_device = false;
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



  cl::Context context(device);
  cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);


  std::cout << "Loading: '" << xclbinFilename << "'\n";
  std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
  bin_file.seekg (0, bin_file.end);
  unsigned nb = bin_file.tellg();
  bin_file.seekg (0, bin_file.beg);
  char *buf = new char [nb];
  bin_file.read(buf, nb);
  cl::Program::Binaries bins;
  bins.push_back({buf,nb});
  devices.resize(1);
  cl::Program program(context, devices, bins);
  cl::Kernel krnl_image_thresholding(program,"image_thresholding_kernel");

  cl::Buffer buffer_in(context,  CL_MEM_READ_ONLY, size_in_bytes);
  cl::Buffer buffer_out(context, CL_MEM_WRITE_ONLY, size_in_bytes);

  int narg=0;
  krnl_image_thresholding.setArg(narg++, buffer_in);
  krnl_image_thresholding.setArg(narg++, buffer_out);
  krnl_image_thresholding.setArg(narg++, grey_image.cols);
  krnl_image_thresholding.setArg(narg++, grey_image.rows);
  krnl_image_thresholding.setArg(narg++, threshold_value);
  krnl_image_thresholding.setArg(narg++, max_binary_value);

  unsigned char *ptr_in = (unsigned char  *) q.enqueueMapBuffer (buffer_in ,  CL_TRUE , CL_MAP_WRITE , 0, size_in_bytes);
  unsigned char *ptr_out = (unsigned char *) q.enqueueMapBuffer (buffer_out , CL_TRUE , CL_MAP_READ  , 0, size_in_bytes);


  for (unsigned int i = 0; i< size_in_bytes; i++) {
  	ptr_in[i] = grey_image.data[i];
  }
  dst.data =  ptr_out;


  q.enqueueMigrateMemObjects({buffer_in},0/* 0 means from host*/);
  q.enqueueTask(krnl_image_thresholding);
  q.enqueueMigrateMemObjects({buffer_out},CL_MIGRATE_MEM_OBJECT_HOST);
  q.finish();

  imwrite("grey_threshold.jpg", dst);

  threshold( grey_image, dst_golden, threshold_value, max_binary_value, THRESH_BINARY );

  imwrite("grey_threshold-golden.jpg", dst_golden);

  for (int i = 0; i < grey_image.rows*grey_image.cols; i++) {
	if (dst.data[i] != dst_golden.data[i]) {
		std::cout << " Error at " << i
				  << " hardware dst.data = " << dst.data
               	  << " dst_golden = " << dst_golden.data
                   << std::endl;
		status = -1;
        break;
	}
  }

  cout << "Bye thresholding image" << endl;


  return status;



}


