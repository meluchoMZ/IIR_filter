/**
  High level 32 bit floating point filter
  Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include "32_bit_filter.h"

static float w1, w2, w3;

float filter(float input, bool reset)
{
	#pragma HLS pipeline II=1
	float w0, output;
	float partial_output_1, partial_output_2, ponderated_output;
	if (reset) {
		w1 = 0; w2 = 0; w3 = 0;
		partial_output_1 = 0; partial_output_2 = 0;
		ponderated_output =0;
		output= 0;
	} else {
		w0 = input + (1.475f*w1) - (0.5984f*w2) + (0.23f*w3);
		partial_output_2 = w2 + w3;
		w3 = w2;
		partial_output_1 = w0 + w1;
		w2 = w1;
		ponderated_output = partial_output_1 + partial_output_2;
		w1 = w0;
		output = 0.027467f*ponderated_output;
	}
	return output;
}
