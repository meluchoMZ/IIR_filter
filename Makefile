x64:
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o f16_x64 16_bit_test.cpp 16_bit_filter.cpp -lsystemc -lm -g
	gcc -o c_test testbench.c

x86:
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux -Wl,-rpath=$SYSTEMC_HOME/lib-linux -o f16_x86 16_bit_filter.cpp -lsystemc -lm -g
	gcc -o c_test testbench.c

clean:
	rm f16_x64 f16_x86 c_test
