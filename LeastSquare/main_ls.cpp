#include <stdio.h> 
#include <gsl/gsl_linalg.h>

#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")

int SolveLS (double a[], double b[], double x[], int neq, int nvar)
{
	// get A
	gsl_matrix_view av = gsl_matrix_view_array (a, neq, nvar);
    gsl_matrix_view bv = gsl_matrix_view_array (b, neq, 1);

	// assume neq > nvar
	
	gsl_matrix *ATA = gsl_matrix_alloc (nvar, nvar);

	gsl_linalg_matmult_mod (&av.matrix, GSL_LINALG_MOD_TRANSPOSE, 
		&av.matrix, GSL_LINALG_MOD_NONE, ATA);

	gsl_matrix *ATb = gsl_matrix_alloc (nvar, 1);
	gsl_linalg_matmult_mod (&av.matrix, GSL_LINALG_MOD_TRANSPOSE,
		&bv.matrix, GSL_LINALG_MOD_NONE, ATb);
		
	gsl_vector_view atbv = gsl_matrix_column (ATb, 0);
	gsl_vector *xv = gsl_vector_alloc (nvar);
    gsl_permutation * p = gsl_permutation_alloc (nvar);
	
    int s;

	gsl_matrix_fprintf (stdout, ATA, "%g");

    gsl_linalg_LU_decomp (ATA, p, &s);
    gsl_linalg_LU_solve (ATA, p, &atbv.vector, xv);

	//gsl_vector_fprintf (stdout, xv, "%g");

	// copy back to x
	for (int i = 0; i < nvar; i++) 
		x[i] = gsl_vector_get (xv,i);
	return 1;
}

void main ()
{

	// full column rank
	double a3[] = {1,0,
				   1,1,
				   0,1};
	double b3[] = {1,2,-1};
	double x3[2];
	SolveLS (a3, b3, x3, 3, 2);
	printf ("x3: %f %f\n", x3[0],x3[1]);

	system ("pause");
}
