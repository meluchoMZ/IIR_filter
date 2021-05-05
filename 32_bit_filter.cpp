/**
  High level 32 bit floating point filter
  Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include <iostream>
#include "32_bit_filter.h"

static float w1, w2, w3;

float filter(float input, bool reset)
{
	#pragma HLS pipeline II=1
	float w0, output;
	if (reset) {
		w1 = 0; w2 = 0; w3 = 0;
		output= 0;
	} else {
		w0 = input + (1.475*w1) - (0.5984*w2) + (0.23*w3);
		output = 0.027467*(w0+w1+w2+w3);
		w3=w2; w2=w1; w1=w0;
	}
	return output;
}
