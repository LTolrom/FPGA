
#include "simple_calculator.h"




void simple_calculator(
		int5 a,
		int5 b,

		bool hex_dec,
		uint4 code,

		uint4 select_digit,

		uint16 *leds,

		uint8 *segment_data,
		uint4 *segment_enable
	) {

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=a
#pragma HLS INTERFACE ap_none port=b
#pragma HLS INTERFACE ap_none port=hex_dec
#pragma HLS INTERFACE ap_none port=code
#pragma HLS INTERFACE ap_none port=select_digit
#pragma HLS INTERFACE ap_none port=segment_data
#pragma HLS INTERFACE ap_none port=segment_enable
#pragma HLS INTERFACE ap_none port=leds



	int10 result=0;


	result = operations(a, b, code);

	short int d0 = 0, d1 = 0, d2 = 0, d3 = 0;
	extract_digits(hex_dec, result, d0, d1, d2, d3);
	display_digits( d0, d1, d2, d3, select_digit, segment_data, segment_enable);


	*leds = (code, hex_dec, (ap_uint<1>)0b0, b, a);




}
