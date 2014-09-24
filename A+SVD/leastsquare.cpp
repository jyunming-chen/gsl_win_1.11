#include <gsl/gsl_linalg.h>


int solve (double a[], double b[], double x[], int neq, int nvar)
{

	// get A
	gsl_matrix_view av = gsl_matrix_view_array (a, neq, nvar);
	
	// compute inverse of (AAT)
	gsl_matrix *aat = gsl_matrix_alloc (neq,neq);
	gsl_linalg_matmult_mod (&(av.matrix), GSL_LINALG_MOD_NONE, &(av.matrix), GSL_LINALG_MOD_TRANSPOSE, aat);
	int signum;
	gsl_permutation *p = gsl_permutation_alloc (neq);
	gsl_linalg_LU_decomp (aat, p, &signum);

	double det;
	printf ("det: %e\n", det = gsl_linalg_LU_det (aat, signum));
	if (det == 0.0) {
		printf ("(AAT) singular ... exiting\n");
		return 0;
	}
	
	gsl_matrix *aatinv = gsl_matrix_alloc(neq,neq);
	gsl_linalg_LU_invert (aat, p, aatinv);

	// A+ = AT (AAT)-1
	gsl_matrix *aplus = gsl_matrix_alloc (nvar,neq); 
	gsl_linalg_matmult_mod (&(av.matrix), GSL_LINALG_MOD_TRANSPOSE, aatinv, GSL_LINALG_MOD_NONE, aplus);
	
	// x = A+ b
	gsl_vector_view bv = gsl_vector_view_array (b, neq);
	gsl_matrix_view bmv = gsl_matrix_view_vector (&(bv.vector), neq,1);

	gsl_matrix *xx = gsl_matrix_alloc (nvar,1);
	gsl_linalg_matmult (aplus, &(bmv.matrix), xx);
	gsl_matrix_fprintf (stdout, xx, "%g");
	
	for (int i = 0; i < nvar; i++) 
		x[i] = gsl_matrix_get (xx, i, 0);

	gsl_permutation_free (p);
	gsl_matrix_free (aat); gsl_matrix_free (aatinv); gsl_matrix_free (aplus); gsl_matrix_free (xx);

	return 1;
}


main ()
{
	int ok;
#if 0
	double a[] = {1,3,
		          2,2};
	double b[] = {4,4};
	
	double x[2];
	ok = solve (a, b, x, 2, 2);
	if (ok) printf ("x: %f %f\n", x[0],x[1]);


	double a2[] = {1,1,0,
				   0,1,1};
	double b2[] = {2,0};
	double x2[3];
	ok = solve (a2, b2, x2, 2, 3);
	if (ok) printf ("x2: %f %f %f\n", x2[0],x2[1],x2[2]);
#endif

	double a3[] = {1,0,
				   1,1,
				   0,1};
	double b3[] = {1,2,-1};
	double x3[2];
	ok = solve (a3, b3, x3, 3, 2);
	if (ok) printf ("x3: %f %f\n", x3[0],x3[1]);

#if 0
	double a4[] = {2,2,
		          1,1};
	double b4[] = {8,3};
	
	double x4[2];
	ok = solve (a4, b4, x4, 2, 2);
	if (ok) printf ("x4: %f %f\n", x4[0],x4[1]);
#endif
}
