#include <stdio.h>
#include <gsl/gsl_linalg.h>
 
#pragma comment (lib, "cblas_d.lib")
#pragma comment (lib, "gsl_d.lib")

int
 main (void)
 {
   double a_data[] = {10, 7, 8, 7,
				7, 5, 6, 5,
				8, 6, 10,9,
				7, 5, 9,10};
   double v_data[] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
   double b_data[] = {32, 23, 33, 31};

   gsl_matrix_view m 
	 = gsl_matrix_view_array (a_data, 4, 4);
   gsl_matrix_view v 
	 = gsl_matrix_view_array (v_data, 4, 4);
 
   gsl_vector_view b
	 = gsl_vector_view_array (b_data, 4);
 
   gsl_vector *S = gsl_vector_alloc (4);
   gsl_vector *work = gsl_vector_alloc (4);
   gsl_vector *x = gsl_vector_alloc(4);  
 
	gsl_linalg_SV_decomp (&m.matrix, &v.matrix, S, work);

	gsl_matrix_fprintf (stdout, &v.matrix, "%g");
	gsl_linalg_SV_solve (&m.matrix, &v.matrix, S, &b.vector, x);

	  
   printf ("x = \n");
   gsl_vector_fprintf (stdout, x, "%g");
 
   gsl_vector_free (x);
   return 0;
 }
