#include "scanner_fit.h"
#include "mpfit.h"
#include <xc.h>

//vars taken from testmpfit.c, distributed with cmpfit-1.3a
//function modified from the test quadratic function
//printresult taken from testmpfit.c

/* This is the private data structure which contains the data points
   and their uncertainties */
struct vars_struct {
  unsigned long int *x;
  unsigned long int *y;
  float *ey;
};

int find_fit(unsigned long int *x_results, unsigned long int *y_results, float *ey,  mp_result **result_target, double **pars, int size){
  //initialize variables
  double perror[NUM_PARAM];
  struct vars_struct v;
  int status;
  int i;
  mp_result result;

  //set starting conditions, best guess
  

  memset(&result,0,sizeof(result));       /* Zero results structure */
  result.xerror = perror;

  //set the error for each reading at a constant 0.2
  for (i = 0; i < size; i++) ey[i] = CONST_ERR;

  //put the results in the mpfit variable structure
  v.x = x_results;
  v.y = y_results;
  v.ey = ey;

  /* struct mp_config_struct c; */
  /* c.ftol = 1e-20; */
  /* c.xtol = 1e-20; */
  /* c.gtol = 1e-20; */
  /* c.epsfcn = MP_MACHEP0; */
  /* c.covtol = 1e-14; */
  /* c.stepfactor = 1e-100; */
  /* c.maxiter = 200; */

  //run the fit
  status = mpfit(quartic_function, 
                 size, 
                 NUM_PARAM, 
                 *pars, 
                 0, 
                 (void *) 0,
                 (void *) &v,
                 &result);

  //populate the outputs
  
  *result_target = &result;
  
  double p1 = 0;
  p1 = **pars;
  Nop();
  
  return 0;
}

/* 
 * quadratic fit function
 *
 * m - number of data points
 * n - number of parameters (2)
 * p - array of fit parameters 
 * dy - array of residuals to be returned
 * vars - private data (struct vars_struct *)
 *
 * RETURNS: error code (0 = success)
 */
int quartic_function(int m, int n, double *p, double *dy, double **dvec, void *vars)
{
  int i;
  struct vars_struct *v = (struct vars_struct *) vars;
  unsigned long int *x, *y;
  float *ey;

  x = v->x;
  y = v->y;
  ey = v->ey;

  /* printf ("quadfunc %f %f %f\n", p[0], p[1], p[2]); */

  for (i=0; i<m; i++) {
    dy[i] = (y[i] - p[0] 
                  - p[1]*x[i] 
                  - p[2]*x[i]*x[i] 
                  - p[3]*x[i]*x[i]*x[i]
                  - p[4]*x[i]*x[i]*x[i]*x[i])/ey[i];
  }

  return 0;
}

