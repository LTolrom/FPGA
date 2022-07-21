
#include <iostream>
#include "simple_calculator-tb.h"



int main() {

	int status = 0;

	int5 a;
	int5 b;

	bool hex_dec;
	uint4 code;

	uint4 select_digit;

	uint8 segment_data_hw;
	uint4 segment_enable_hw;

	uint8 segment_data_sw;
	uint4 segment_enable_sw;


	uint16 leds_hw;
	uint16 leds_sw;


	for (int i = 0; (i < 32) && (status == 0); i++) {
		for (int j = 0; (j < 32) && (status == 0); j++) {
			for (int c = 0; (c < 8) && (status == 0); c++) {
				for (int k = 0; (k < 2) && (status == 0); k++) {
					for (int l = 0; (l < 4) && (status == 0); l++) {

						a = (int5)i;
						b = (int5)j;
						code = (uint4)c;
						hex_dec = (bool)k;
						select_digit =(uint4) 1 << l;


						simple_calculator( a, b, hex_dec, code, select_digit, &leds_hw, &segment_data_hw, &segment_enable_hw);
						simple_calculator_sw( a, b, hex_dec, code, select_digit, &leds_sw, &segment_data_sw, &segment_enable_sw);

						if ( 	(segment_data_hw != segment_data_sw) ||
										(segment_enable_hw != segment_enable_sw) ||
										(leds_hw != leds_sw) )
								{
									status = -1;

									std::cout << "Error at "<<
											     "    a = " << a.to_string() <<
												 "    b = " << b.to_string() <<
												 "    hex_dec = " << hex_dec <<
												 "    code = " << code.to_string() <<
												 "    select_digit = " << select_digit.to_string() <<
												 "-----------> segment_data_hw = " << segment_data_hw.to_string() <<
												 "    segment_data_sw = " << segment_data_sw.to_string() <<
												 "    segment_enable_hw = " << segment_enable_hw.to_string() <<
												 "    segment_enable_sw = " << segment_enable_sw.to_string() <<
												 std::endl;
								}
							}
						}
					}
				}
			}


	if (status == 0) {
		std::cout << "Test Passed!" << std::endl;
	} else {
		std::cout << "Test Failed!" << std::endl;
	}

	return status;

}
