/**
  High level 32 bit floating point filter test
  Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include <iostream>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "32_bit_filter.h"

#define INF "./source_1.dat"
#define TESTF "./test_1.dat" 

int main(void)
{
	FILE *f_input, *f_test;
	float input, output, computed_output;

	if ((f_input = fopen(INF, "r")) == NULL) {
		std::cout << "ERROR: cannot open input file " << INF << ": " << strerror(errno) << std::endl;
		return EXIT_FAILURE;
	}
	if ((f_test = fopen(TESTF, "r")) == NULL) {
		std::cout << "ERROR: cannot open test file " << TESTF << ": " << strerror(errno) << std::endl;
		fclose(f_input); f_input = NULL;
		return EXIT_FAILURE;
	}

	int i = 0;
	while (fscanf(f_input, "%f ", &input) != EOF)
	{
		fscanf(f_test, "%f ", &output);
		computed_output = filter((float)input, false);
		if (output != computed_output) {
			if (! ((isnan(output) && isnan(computed_output)))) {
				std::cout << ": Failure on test: " << computed_output << " != " << output << std::endl;
			}
		}
	}
	std::cout << "END" << std::endl;
	fclose(f_input); f_input = NULL;
	fclose(f_test); f_test = NULL;

	return EXIT_SUCCESS;
}
