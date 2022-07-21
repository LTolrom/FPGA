#include <iostream>
#include <fstream>
#include <sstream>

int spm_get_size(
		char         *inFilename,
		unsigned int &row_size,
		unsigned int &col_size,
		unsigned int &data_size) {

	std::ifstream spm_file(inFilename);
	if(spm_file.fail()){
		std::cout << "Sparse matrix file " << inFilename << " doesn't exist!" << std::endl;
		return -1;
	}

	std::string line;
	std::stringstream tokenizer;

	while (getline (spm_file, line)) {

		if (line[0] != '%') {
			unsigned int r, c, d;
			tokenizer << line;
			tokenizer >> r >>  c >> d;

			row_size = r;
			col_size = c;
			data_size = d;



			std::cout << "\r row_size = " <<  row_size << std::endl;
			std::cout << "\r col_size = " <<  col_size << std::endl;
			std::cout << "\r data_size = " << data_size << std::endl;

			break;
		}
	}
	spm_file.close();
	return 0;
}

unsigned int  read_mtx_spm(
		char  *inFilename,
		float *values,
		unsigned int    *colIndices,
		unsigned int    *rowPtr) {

	std::ifstream spm_file(inFilename);
	if(spm_file.fail()){
		std::cout << "Sparse matrix file " << inFilename << " doesn't exist!" << std::endl;
		return -1;
	}

	std::string line;

	unsigned int n;
	unsigned int m;
	unsigned int nnz;

	while (getline (spm_file, line)) {

		if (line[0] != '%') {

			std::stringstream tokenizer;
			tokenizer << line;
			tokenizer >> n >>  m >> nnz;



			unsigned int line_number = 0;
			while (getline (spm_file, line)) {// read a line from a file
				if ( line_number < nnz) {

					float v;
					unsigned int c;
					std::stringstream tokenizer;
					tokenizer << line;
					tokenizer >> c >> v;

					colIndices[line_number] = c;

					values[line_number] = v;

				} else {
					unsigned int r;
					std::stringstream tokenizer;
					tokenizer << line;
					tokenizer >> r;
					rowPtr[line_number-nnz] = r;
				}
				line_number++;
			}
		}
	}
	spm_file.close();
	return 0;
}
