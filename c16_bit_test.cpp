#include <iostream>
#include <errno.h>
#include <string.h>
#include "c16_bit_filter.h"

#define INF "./source_0.dat"
#define TESTF "./test_0.dat" 

int main(void)
{
	FILE *f_input, *f_test;
	int input, output, computed_output;

	if ((f_input = fopen(INF, "r")) == NULL) {
		std::cout << "ERROR: cannot open input file " << INF << ": " << strerror(errno) << std::endl;
		return EXIT_FAILURE;
	}
	if ((f_test = fopen(TESTF, "r")) == NULL) {
		std::cout << "ERROR: cannot open test file " << TESTF << ": " << strerror(errno) << std::endl;
		fclose(f_input); f_input = NULL;
		return EXIT_FAILURE;
	}
	

	computed_output = filter((short) 0, true); // reset da igual a entrada
	fscanf(f_test, "%d ", &output);
	if (output != computed_output) {
		std::cout << "Failure on reset: " << computed_output << " != " << output << std::endl;
	}
	while (fscanf(f_input, "%d ", &input) != EOF)
	{
		fscanf(f_test, "%d ", &output);
		computed_output = filter((short)input, false);
		if (output != computed_output) {
			std::cout << "Failure on test: " << computed_output << " != " << output << std::endl; 
		}
	}
	std::cout << "END" << std::endl;
	fclose(f_input); f_input = NULL;
	fclose(f_test); f_test = NULL;

	return EXIT_SUCCESS;
}
