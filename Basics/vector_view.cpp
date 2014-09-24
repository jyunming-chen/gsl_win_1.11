#include <gsl/gsl_linalg.h>
#include <stdio.h>

#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")

void main()
{

	double a[] = {1.0, 2.0, 3.0};

	// gsl_vector_view defined from a[]
	gsl_vector_view v = gsl_vector_view_array (a, 3);
	gsl_vector_fprintf (stdout, &(v.vector), "%g");

	// another vector view defined ALSO on a[]
	gsl_vector_view vv = gsl_vector_view_array (a, 3);


	// notice: they share the same memory
	gsl_vector_set (&(vv.vector), 0, -1.0);
	gsl_vector_fprintf (stdout, &(vv.vector), "%g");

	gsl_vector_fprintf (stdout, &(v.vector), "%g");
}
