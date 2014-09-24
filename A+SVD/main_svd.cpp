#include <gsl/gsl_linalg.h>
#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")


int SolveSVD (double a[], double b[], double x[], int neq, int nvar)
{
	// get A
	gsl_matrix_view av = gsl_matrix_view_array (a, neq, nvar);

	if (neq <  nvar) { // M < N ... do the transposed matrix
		gsl_matrix *atrans = gsl_matrix_alloc (nvar, neq);
		gsl_matrix_transpose_memcpy (atrans, &av.matrix);
		
		gsl_matrix *v = gsl_matrix_alloc (neq, neq);
		gsl_vector *s = gsl_vector_alloc (neq);
		gsl_vector *work = gsl_vector_alloc (neq);
		gsl_linalg_SV_decomp (atrans, v, s, work);
	
		// x = A+ b 
		gsl_matrix *splus = gsl_matrix_calloc (neq, neq);
		
		// compute sigma_plus
		for (int i = 0; i < neq; i++) {
			double sigma;
			if ((sigma = gsl_vector_get (s,i)) != 0.0)
			gsl_matrix_set (splus, i,i, 1.0/sigma);
		}
		
		gsl_linalg_matmult (atrans, splus, atrans);
		gsl_linalg_matmult_mod (atrans, GSL_LINALG_MOD_NONE, v, GSL_LINALG_MOD_TRANSPOSE, atrans);
		
		gsl_vector_view bv = gsl_vector_view_array (b, neq);
		gsl_matrix_view bmv = gsl_matrix_view_vector (&bv.vector, neq, 1);
		gsl_matrix *xx = gsl_matrix_alloc (nvar,1);
		gsl_linalg_matmult (atrans, &bmv.matrix, xx);
		
//		gsl_matrix_fprintf (stdout, xx, "%g");
		
		for (int i = 0; i < nvar; i++) {
			x[i] = gsl_matrix_get(xx,i,0);
		}
		gsl_matrix_free (splus); gsl_matrix_free (xx);
		gsl_matrix_free (atrans);

	gsl_matrix_free (v); gsl_vector_free (s); gsl_vector_free (work);

	} else {  // M >= N
		gsl_matrix *v = gsl_matrix_alloc (nvar, nvar);
		gsl_vector *s = gsl_vector_alloc (nvar);
		gsl_vector *work = gsl_vector_alloc (nvar);
		gsl_linalg_SV_decomp (&av.matrix, v, s, work);
	
		// x = A+ b
		gsl_vector_view bv = gsl_vector_view_array (b, neq);
		gsl_vector *xx = gsl_vector_alloc (nvar);
		gsl_linalg_SV_solve (&av.matrix, v, s, &bv.vector, xx);
		
//		gsl_vector_fprintf (stdout, xx, "%g");
		for (int i = 0; i < nvar; i++) 
			x[i] = gsl_vector_get (xx, i);
			
		gsl_vector_free (xx);

	gsl_matrix_free (v); gsl_vector_free (s); gsl_vector_free (work);

	}
	


	return 1;
}


void main ()
{
	// full rank
	double a[] = {1,3,
		          2,2};
	double b[] = {4,4};
	
	double x[2];
	SolveSVD (a, b, x, 2, 2);
	printf ("x: %f %f\n", x[0],x[1]);

	// full row rank
	double a2[] = {1,1,0,
				   0,1,1};
	double b2[] = {2,0};
	double x2[3];
	SolveSVD (a2, b2, x2, 2, 3);
	printf ("x2: %f %f %f\n", x2[0],x2[1],x2[2]);

	// full column rank
	double a3[] = {1,0,
				   1,1,
				   0,1};
	double b3[] = {1,2,-1};
	double x3[2];
	SolveSVD (a3, b3, x3, 3, 2);
	printf ("x3: %f %f\n", x3[0],x3[1]);

	// none of the above
	double a4[] = {2,2,
		          1,1};
	double b4[] = {8,3};
	
	double x4[2];
	SolveSVD (a4, b4, x4, 2, 2);
	printf ("x4: %f %f\n", x4[0],x4[1]);

	system ("pause");
}
