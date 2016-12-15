#include "mpfit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_fit(unsigned long int *x_results, unsigned long int *y_results, float *ey, mp_result **result, double **pars, int size);
int quartic_function(int m, int n, double *p, double *dy, double **dvec, void *vars);

#define CONST_ERR 0.2
#define NUM_PARAM 5
