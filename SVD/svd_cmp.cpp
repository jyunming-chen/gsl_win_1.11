 #include <stdio.h>
     #include <gsl/gsl_linalg.h>
     
     int
     main (void)
     {
	   double a_data[] = {1, 0,
						  1, 1,
						  0, 1};

       gsl_matrix_view a 
         = gsl_matrix_view_array (a_data, 3, 2);
       gsl_matrix *v = gsl_matrix_alloc (2,2);
     
       gsl_vector *S = gsl_vector_alloc (2);
       gsl_vector *work = gsl_vector_alloc (2);
     
		gsl_linalg_SV_decomp (&a.matrix, v, S, work);

		printf ("U:\n");
		gsl_matrix_fprintf (stdout, &a.matrix, "%g");
		printf ("S:\n");
		gsl_vector_fprintf (stdout, S, "%g");
		printf ("V:\n");
		gsl_matrix_fprintf (stdout, v, "%g");

		system("Pause");

		return 0;
     }
