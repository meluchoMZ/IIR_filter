/**
  High level 16 bit filter
  Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include <iostream>

static short w1, w2, w3;

short filter(short input, bool reset)
{
	#pragma HLS pipeline II=2
	short w0, output;
	if (reset) {
		w1 = 0; w2 = 0; w3 = 0;
		output= 0;
	} else {
		w0 = input + ((w1<<4)-(w1<<1))-((w2<<2)+w2)+(w3<<1);
		output = (w0+w1+w2+w3) << 1;
		w3=w2; w2=w1; w1=w0;
	}
	return output;
}
