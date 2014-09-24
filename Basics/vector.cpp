#include <gsl/gsl_linalg.h>
#include <stdio.h>

#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")

void main()
{
	// gsl_vector
	gsl_vector *x = gsl_vector_alloc (4);
	gsl_vector *y = gsl_vector_alloc (4);

	for (int i = 0; i < 4; i++) {
		gsl_vector_set (x, i, (double)i);    // [0,1,2,3]
		gsl_vector_set (y, i, (double)i*10); // [0, 10, 20, 30]
	}

	gsl_vector_add (x, y);   // x[ 0,11, 22, 33]
	gsl_vector_fprintf (stdout, x, "%g");


	// gsl_vector_view
	double a[] = {1.0, 2.0, 3.0};
	gsl_vector_view v = gsl_vector_view_array (a, 3);
	gsl_vector_fprintf (stdout, &(v.vector), "%g");

}
