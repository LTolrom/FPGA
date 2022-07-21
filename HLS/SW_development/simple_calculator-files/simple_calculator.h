
#ifndef __SIMPLE_CALCULATOR_H__
#define __SIMPLE_CALCULATOR_H__

#include <ap_int.h>


typedef ap_int<5>    int5;
typedef ap_uint<4>   uint4;

typedef ap_int<10>   int10;
typedef ap_uint<10>  uint10;

typedef ap_uint<8>   uint8;
typedef ap_uint<16>  uint16;


const unsigned int seven_segment_negative = 0b10111111;
const unsigned int seven_segment_off      = 0b11111111;

const unsigned int seven_segment_code[16] = {
		0b11000000,  // 0
		0b11111001,  // 1
		0b10100100,  // 2
		0b10110000,  // 3
		0b10011001,  // 4
		0b10010010,  // 5
		0b10000010,  // 6
		0b11111000,  // 7
		0b10000000,  // 8
		0b10010000,  // 9
		0b10001000,  // a
		0b10000011,  // b
		0b11000110,  // c
		0b10100001,  // d
		0b10000110,  // e
		0b10001110,  // f

};

int10 operations(
		int5 a,
		int5 b,


		uint4 code);


void extract_digits(
		bool  hex_dec,
		int10 result,
		short int &d0,
		short int &d1,
		short int &d2,
		short int &d3);


void display_digits(

		short int d0,
		short int d1,
		short int d2,
		short int d3,

		uint4     select_digit,

		uint8    *segment_data,
		uint4    *segment_enable);

#endif //__SIMPLE_CALCULATOR_H__
