#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <math.h>

#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")

////////////////////////////////////////////////////////////
// Solve A^-1 with LU and verify
int main(int argc, char **argv)
{
    double a_data[] = { 0,1,1,3,2,
                        1,2,2,1,1,
                        1,2,9,1,5,
                        3,1,1,7,1,
                        2,1,5,1,8 };

    gsl_permutation * p = gsl_permutation_alloc (5);
    gsl_matrix_view m 
        = gsl_matrix_view_array(a_data, 5, 5);
	gsl_matrix *acopy = gsl_matrix_alloc (5,5);
	gsl_matrix_memcpy (acopy, &m.matrix);

    int s;

    gsl_linalg_LU_decomp (&m.matrix, p, &s);
	gsl_matrix *inverse = gsl_matrix_alloc (5,5);
	int ans = gsl_linalg_LU_invert (&m.matrix, p, inverse);

	gsl_matrix *result = gsl_matrix_alloc(5,5);
	
	gsl_linalg_matmult (acopy, inverse, result);
	printf ("A.A^-1 = I...\n");
	gsl_matrix_fprintf (stdout, result, "%g");
	gsl_matrix_free (result);

	//////////// singular, but it seems that gsl doesn't know !? ////
    double aa_data[] = { 1,2,1,
		                2,4,2,
						1,2,9};

    gsl_permutation * pp = gsl_permutation_alloc (3);
    gsl_matrix_view mm 
        = gsl_matrix_view_array(aa_data, 3, 3);
    gsl_linalg_LU_decomp (&mm.matrix, pp, &s);
	gsl_matrix *iinverse = gsl_matrix_alloc (3,3);
	ans = gsl_linalg_LU_invert (&mm.matrix, pp, iinverse);

	double det; 
	printf ("det: %e\n", det = gsl_linalg_LU_det (&mm.matrix, s));
	
	if (fabs(det) > 1e-10) {
		printf ("A.A^-1 = I...\n");
		gsl_matrix_fprintf (stdout, iinverse, "%g");
	}

	system("pause");
}
