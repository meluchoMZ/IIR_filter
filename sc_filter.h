/**
  IIR filter
 Hardware Software codesign, Computer engineering 
Author: Miguel Blanco Godón
*/

#include <systemc.h>

SC_MODULE(filter)
{
	public:
		sc_in< bool > clk, rst;
		sc_in< sc_int< 16 > > i;
		sc_out< sc_int< 16 > > o;
		sc_out< bool > valid_output;

		void execute(void);

		SC_CTOR(filter)
		{
			SC_METHOD(execute);
			sensitive << clk.pos();
		}
	private:
		sc_int< 16 > w1, w2, w3;
};
