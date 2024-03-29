#include "splines.h"

#include <stdlib.h>

#define MALLOC_FAILED( P, SIZE ) (((P)=malloc( (SIZE)*sizeof( *(P))))==NULL)

int
alloc_spl (spline_t * spl, int n)
{
  spl->n = n;
  return MALLOC_FAILED (spl->x, spl->n)
    || MALLOC_FAILED (spl->f, spl->n)
    || MALLOC_FAILED (spl->f1, spl->n)
    || MALLOC_FAILED (spl->f2, spl->n)
    || MALLOC_FAILED (spl->f3, spl->n);
}

int
read_spl (FILE * inf, spline_t * spl)
{
  int i;
  if (fscanf (inf, "%d", &(spl->n)) != 1 || spl->n < 0)
    return 1;

  if (alloc_spl (spl, spl->n))
    return 1;

  for (i = 0; i < spl->n; i++)
    if (fscanf
        (inf, "%lf %lf %lf %lf %lf", spl->x + i, spl->f + i, spl->f1 + i,
         spl->f2 + i, spl->f3 + i) != 5)
      return 1;

  return 0;
}

void
write_spl (spline_t * spl, FILE * ouf)
{
  int i;
  fprintf (ouf, "%d\n", spl->n);
  for (i = 0; i < spl->n; i++)
    fprintf (ouf, "%g %g %g %g %g\n", spl->x[i], spl->f[i], spl->f1[i],
             spl->f2[i], spl->f3[i]);
}

double
value_spl (spline_t * spl, double x)
{
  double value = 0.0 , temp;
  int i,j;

  for(i = 0; i < 5; i++){
    temp = spl->f[i];
    for(j = 0; j < i; j++ )
      temp *= x;
    value += temp;
  }

  return value;
}
