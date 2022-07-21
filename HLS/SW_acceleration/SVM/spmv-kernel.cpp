
#define DIM 10098



extern "C" {
	void spmv_kernel(
		double* values,
		int* col_indices,
		int* row_indices,
		double* x,
		double* y,
		int start,
		int end,
		int n,
		int m) {
#pragma HLS INTERFACE m_axi bundle=gmem_0 port=values
#pragma HLS INTERFACE m_axi bundle=gmem_1 port=col_indices

#pragma HLS INTERFACE m_axi bundle=gmem_0 port=x
#pragma HLS INTERFACE m_axi bundle=gmem_0 port=y
#pragma HLS INTERFACE m_axi bundle=gmem_0 port=row_indices




		double x_local[DIM];
		double y_local[DIM];
		int row_indices_diff_local[DIM];


		int nnz = 0;
		for (int i = 0; i < m; i++) {
			x_local[i] = x[i];
		}

		int previous_row_index;
		for (int i = 0; i < n + 1; i++) {
			 int row_index = row_indices[i];
			if (i > 0) {
				row_indices_diff_local[i - 1] = row_index - previous_row_index;
				nnz += row_index - previous_row_index;;
			}
			previous_row_index = row_index;
		}


		double y_previous_break = 0.0;
		double y_all_row = 0.0;
		int j = 0;
		int remained_row_index = row_indices_diff_local[j++];
		for (int i = 0; i < nnz; ++i) {
			int k = col_indices[i];
			double y_t = values[i] * x_local[k];
			y_all_row += y_t;

			remained_row_index--;
			if (remained_row_index == 0) {
				y_local[j - 1] = y_all_row - y_previous_break;
				y_previous_break = y_all_row;
				remained_row_index = row_indices_diff_local[j++];
			}
		}
		for (int i = 0; i < n; i++) {
			y[i] = y_local[i];
		}


	}
}
