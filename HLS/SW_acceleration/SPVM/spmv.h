#pragma once

void spm_get_size(
		char         *inputFile,
		unsigned int &row_size,
		unsigned int &col_size,
		unsigned int &data_size);

unsigned int  read_mtx_spm(
		char  *inFilename,
		float *values,
		unsigned int    *colIndices,
		unsigned int    *rowPtr);


//OCL_CHECK doesn't work if call has templatized function call
#define OCL_CHECK(error,call)                                       \
    call;                                                           \
    if (error != CL_SUCCESS) {                                      \
      printf("%s:%d Error calling " #call ", error code is: %d\n",  \
              __FILE__,__LINE__, error);                            \
      exit(EXIT_FAILURE);                                           \
    }
