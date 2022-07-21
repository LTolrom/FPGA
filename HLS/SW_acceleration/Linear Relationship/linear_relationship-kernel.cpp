

extern "C" {

void linear_relationship_kernel(
		float *A, float *B, float *C,
		float alpha, float beta, float gamma,
		unsigned int n) {

#pragma HLS INTERFACE m_axi port=A bundle=gmem_0
#pragma HLS INTERFACE m_axi port=B bundle=gmem_1

	for (unsigned int i = 0; i < n; i++) {
		C[i] =  alpha*A[i] + beta*B[i] + gamma;
	}
}
}
