
#include "leading_one.h"

ap_int<5> leading_one(ap_uint<9> a) {
#pragma HLS INTERFACE ap_none port=a
#pragma HLS INTERFACE ap_ctrl_none port=return



	ap_int<5> index;

	if (a[8] == 1) {
		index = 8;
	} else if (a[7] == 1) {
		index = 7;
	} else	if (a[6] == 1) {
		index = 6;
	} else	if (a[5] == 1) {
		index = 5;
	} else	if (a[4] == 1) {
		index = 4;
	} else	if (a[3] == 1) {
		index = 3;
	} else	if (a[2] == 1) {
		index = 2;
	} else	if (a[1] == 1) {
		index = 1;
	} else	if (a[0] == 1) {
		index = 0;
	} else {
		index = -1;
	}



	return index;
}
