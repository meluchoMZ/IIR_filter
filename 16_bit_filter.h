/**
  IIR filter
 Hardware Software codesign, Computer engineering 
Author: Miguel Blanco Godón
*/

#include <systemc.h>

SC_MODULE(filter)
{
	public:
		sc_in< bool > clk, reset;
		sc_in< sc_int< 16 > > input;
		sc_out< sc_int< 16 > > output;
		sc_out< bool > valid_output;

		void execute(void);

		SC_CTOR(filter)
		{
			SC_METHOD(execute);
			sensitive << clk.pos();
		}
	private:
		// rexistros internos para gardar os valores w(i) anteriormente calculados
		sc_int< 16 > w0, w1, w2, w3;
};
