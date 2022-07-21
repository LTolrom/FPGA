#define M_MAX 10240

//------------------------------------------------------
//         06
//------------------------------------------------------
extern "C" {
void mxv_kernel(
    float *A, float *x, float *y,
    unsigned int n, unsigned m) {


    float x_local[M_MAX];
    float y_local[M_MAX];

    L1: for (int i = 0; i < m; i++) {
        x_local[i] = x[i];
    }

    double y_total = 0;
    double y_break = 0;
    L2: for (int p = 0; p < n*m; p++) {
        int i = p/m;
        int j = p%m;
        y_total += A[i*m+j]*x_local[j];

        if (j == m-1) {
            y_local[i] =  y_total - y_break;
            y_break    =  y_total;
        }
    }

    L3: for (int i = 0; i < n; i++) {
        y[i] = y_local[i];
    }
}
}
