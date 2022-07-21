
#include "simple_calculator.h"

uint8 seven_segment_digit_code (short int d) {

	uint8 segment_data;
	switch(d) {
	case 0:
		segment_data = seven_segment_code[0];
		break;
	case 1:
		segment_data = seven_segment_code[1];
		break;
	case 2:
		segment_data = seven_segment_code[2];
		break;
	case 3:
		segment_data = seven_segment_code[3];
		break;
	case 4:
		segment_data = seven_segment_code[4];
		break;
	case 5:
		segment_data = seven_segment_code[5];
		break;
	case 6:
		segment_data = seven_segment_code[6];
		break;
	case 7:
		segment_data = seven_segment_code[7];
		break;
	case 8:
		segment_data = seven_segment_code[8];
		break;
	case 9:
		segment_data = seven_segment_code[9];
		break;
	case 10:
		segment_data = seven_segment_code[10];
		break;
	case 11:
		segment_data = seven_segment_code[11];
		break;
	case 12:
		segment_data = seven_segment_code[12];
		break;
	case 13:
		segment_data = seven_segment_code[13];
		break;
	case 14:
		segment_data = seven_segment_code[14];
		break;
	case 15:
		segment_data = seven_segment_code[15];
		break;
	default:
		segment_data = seven_segment_off;
		break;
	}


	return segment_data;
}

void display_digits(

		short int d0,
		short int d1,
		short int d2,
		short int d3,

		uint4     select_digit,

		uint8    *segment_data,
		uint4    *segment_enable)
{




	*segment_data   = seven_segment_off;
	*segment_enable = 0b1111;

	uint8 segment_data_0;
	uint8 segment_data_1;
	uint8 segment_data_2;
	uint8 segment_data_3;

	segment_data_0 = seven_segment_digit_code(d0);
	segment_data_1 = seven_segment_digit_code(d1);
	segment_data_2 = seven_segment_digit_code(d2);



	if (select_digit == 0b0001) {
		*segment_data = segment_data_0;
		*segment_enable = 0b1110;
	} else if (select_digit == 0b0010) {
		*segment_data = segment_data_1;
		*segment_enable = 0b1101;
	} else if (select_digit == 0b0100) {
		*segment_data = segment_data_2;
		*segment_enable = 0b1011;
	} else if (select_digit == 0b1000) {
		if (d3 == 1) {
			*segment_data   = seven_segment_negative;
		} else {
			*segment_data   = seven_segment_off;
		}
		*segment_enable = 0b0111;
	} else {
		*segment_data   = seven_segment_off;
		*segment_enable = 0b1111;
	}
}
