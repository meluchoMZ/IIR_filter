/**
 Filter output test 
 Hardware-Software codesign, Computer engineering
Author: Miguel Blanco Godón
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define INF "./source_0.dat"
#define OUTF "./test_0.dat"

int main(void)
{
	FILE *f_input, *f_output; 
	int16_t i, o, w0 = 0, w1 = 0, w2 = 0, w3 = 0;

	if ((f_input = fopen(INF, "r")) == NULL) {
		printf("ERROR: cannot open input file '%s': %s\n", INF, strerror(errno));
		return EXIT_FAILURE;
	}

	if ((f_output = fopen(OUTF, "w")) == NULL) {
		printf("ERROR: cannot open output file '%s': %s\n", OUTF, strerror(errno));
		fclose(f_input);
		return EXIT_FAILURE;
	}

	
	fprintf(f_output, "%d ", 0);
	// process input and write output
	while (fscanf(f_input, "%d ", &i) != EOF)
	{
		w0 = i + 14*w1 - 5*w2 + 2*w3;
		o = 2*(w0+w1+w2+w3);
		w3 = w2; w2 = w1; w1 = w0; 
		fprintf(f_output, "%d ", o);
	}
	fclose(f_input);
	fclose(f_output);

	return EXIT_SUCCESS;
}
