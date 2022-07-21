
#ifndef __SIMPLE_CALCULATOR_TB_H__
#define __SIMPLE_CALCULATOR_TB_H__



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
	);


void simple_calculator_sw(
		int5 a,
		int5 b,

		bool hex_dec,
		uint4 code,

		uint4 select_digit,

		uint16 *leds,

		uint8 *segment_data,
		uint4 *segment_enable
	);

#endif //__SIMPLE_CALCULATOR_TB_H__
