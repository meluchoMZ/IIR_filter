/**
  16 bit signed IIR filter SystemC test
  Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include <systemc.h>
#include "16_bit_filter.h"

char source_file[] = "./source_0.dat";
char test_file[] = "./test_0.dat";

SC_MODULE(producer)
{
	public:
		sc_in<bool> clk, reset;
		sc_out<sc_int<16>> out;

		SC_CTOR(producer)
		{
			file = fopen(source_file, "rt");
			if (!file) {
				cerr << "Cannot find file " << source_file << endl;
				exit(EXIT_FAILURE);
			}
			open = true;
			SC_METHOD(produce);
			sensitive << clk.pos();
		}

		void produce(void)
		{
			if (reset.read()) {
				out.write(0);
			} else {
				if (!open) {
					out->write(0);
					return;
				}
				if(fscanf(file, "%d ", &data) == EOF) {
					fclose(file);
					open = false;
					return;
				}
				out->write(data);
			}
		}
	private:
		FILE *file;
		bool open;
		int data;
};


SC_MODULE(consumer)
{
	public:
		sc_in<bool> clk, reset;
		sc_in<sc_int<16>> res;
		sc_in<bool> valid_res;

		SC_CTOR(consumer)
		{
			file = fopen(test_file, "rt");
			if (!file) {
				cerr << "Cannot find file " << test_file << endl;
				exit(EXIT_FAILURE);
			}
			SC_METHOD(consum);
			sensitive << clk.pos();
		}

		void consum(void)
		{
			if (reset.read()) {
				return;
			}

			if (!valid_res.read()) {
				return;
			}
			
			if(fscanf(file, "%d ", &data) == EOF) {
				fclose(file);
				cout << "END!" << endl;
				sc_stop();
				return;
			}
			data_res = res->read();
			if (data != data_res) {
				printf("FAIL: %d != %d @ %d\n", data_res, data, count);
			}
			count++;
		}
	private:
		FILE *file;
		int16_t data, data_res;
		int count = 1;
};

class top : public sc_module
{
	public:
		sc_in<bool> clk, reset;
		sc_signal<sc_int<16>> data, res;
		sc_signal<bool> val;
		
		producer *prod;
		filter *fil;
		consumer *cons;

		SC_CTOR(top)
		{
			prod = new producer("producer");
			fil = new filter("filter");
			cons = new consumer("consumer");

			prod->clk(clk);
			prod->reset(reset);
			prod->out(data);

			fil->clk(clk);
			fil->rst(reset);
			fil->i(data);
			fil->o(res);
			fil->valid_output(val);
			
			cons->clk(clk);
			cons->reset(reset);
			cons->res(res);
			cons->valid_res(val);
		}
};

int sc_main(int argc, char **argv)
{
	sc_clock clk("clk", 1); 
	sc_signal<bool> reset;

	top top_module("top");
	top_module.clk(clk);
	top_module.reset(reset);

	reset.write(true); sc_start(2, SC_NS);
	reset.write(false); sc_start(10, SC_SEC);
	return EXIT_SUCCESS;
}
