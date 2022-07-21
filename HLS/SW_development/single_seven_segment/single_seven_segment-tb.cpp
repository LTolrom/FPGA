
#include "single_seven_segment-tb.h"
#include <iostream>

unsigned int seven_segment_code[10] =
{
		0b11000000,
		0b11111001,
		0b10100100,
		0b10110000,
		0b10011001,
		0b10010010,
		0b10000010,
		0b11111000,
		0b10000000,
		0b10010000
};

int main() {

	int status = 0;
	ap_uint<8> digit;
	ap_uint<8> code7segment;
	ap_uint<4>  anods;

	for (int i = 0; i < 10; i++) {
		single_seven_segment(i, &code7segment, &anods);
		std::cout << "i = " << i << " code7segment = " << code7segment << "  anods = "<< anods << std::endl;
		if (code7segment != seven_segment_code[i] || anods != 14) {
			status = -1;
			break;
		}
	}


	return status;

}
