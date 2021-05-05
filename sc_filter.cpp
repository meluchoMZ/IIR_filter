/**
  IIR filter behavior implementation
  Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include "16_bit_filter.h"

void filter::execute(void)
{
	//#pragma HLS pipeline II=2
	sc_int<16> w0;
	if (rst->read()) {
		w1 = 0; w2 = 0; w3 = 0;
		valid_output->write(false);
	} else {
		w0 = i->read()+((w1<<4)-(w1<<1))-((w2<<2)+w2)+(w3<<1);
		o->write((w0+w1+w2+w3)<<1);
		valid_output->write(true);
		w3 = w2; w2 = w1; w1 = w0;
	}
}
