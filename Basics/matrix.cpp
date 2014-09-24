#include <gsl/gsl_linalg.h>
#include <stdio.h>

#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")

void main()
{
	// convert array to matrix_view
	double a[] = {1.0, 2.0, 3.0, 2.0, 4.0, 6.0};
	gsl_matrix_view m = gsl_matrix_view_array (a, 2, 2);
	gsl_matrix_fprintf (stdout, &(m.matrix), "%g");

	gsl_matrix_view m = gsl_matrix_view_array (a, 2, 2);


	gsl_matrix_transpose_memcpy ( (&(m.matrix));
	gsl_matrix_fprintf (stdout, &(m.matrix), "%g");

#if 0
	// convert vector to matrix_view
	gsl_vector *v = gsl_vector_alloc (3);
	for (int i = 0; i < 3; i++) gsl_vector_set (v, i, (double)i*10);
	gsl_matrix_view vm = gsl_matrix_view_vector (v, 3, 1);   // vm as column matrix
	gsl_matrix_fprintf (stdout, &(vm.matrix), "%g");

	// matrix multiplication
	gsl_matrix *c = gsl_matrix_alloc (2,1);
	gsl_linalg_matmult (&(m.matrix), &(vm.matrix), c);  // m(2x3) vm (3x1) = c (2x1)
	gsl_matrix_fprintf (stdout, c, "%g");

	// extract vector from matrix (1st column)
	gsl_vector_view vv = gsl_matrix_column (c, 0);
	gsl_vector_fprintf (stdout, &(vv.vector), "%g");
#endif
}
