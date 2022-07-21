
#include "simple_calculator.h"

uint10 div10(uint10 r) {
#pragma HLS INLINE off

	return (r/10);
}

void extract_digits(
		bool  hex_dec,
		int10 result,
		short int &d0,
		short int &d1,
		short int &d2,
		short int &d3) {


	short int sign = 0;
	uint10 r = result;
	if (result < 0) {
		sign = 1;
		r = -result;
	} else {
		sign = 0;
		r = result;
	}

	d0 = 0;
	d1 = 0;
	d2 = 0;
	d3 = 0;

	if (hex_dec == 0) {
		//first decimal digit
		d0 = r-10*div10(r);

		r = r/10;
		//second decimal digit
		d1 = r-10*div10(r);

		r = r/10;
		//third decimal digit
		d2 = r-10*div10(r);
	} else {
		//first decimal digit
		d0 = r(3, 0);
		//second decimal digit
		d1 = r(7, 4);
		//third decimal digit
		d2 = r(9, 8);
	}

	d3 = sign;
}

