 //shphexIGA.c
//Build the data structures defining the structured grid IGA hex elements
#include <FCMangle.h>

int HexIGAShapeAndDrv(int p, int quadPtIndex, double N[], double dN[][1]);

#define shphexiga FortranCInterface_GLOBAL_(shphexiga, SHPHEXIGA)
void shphexIGA(int *p, int quadPtIndex, double N[], double dN[][1])
{

  HexIGAShapeAndDrv(*p,quadPtIndex,N,dN);
}

////////////////////////////////////////////////////////////////////////////////
//compute value of 1D Bernstein polynomial i of order p at point x
//bern returns the value of the berstein polynomial at x in [0,1]
//  INPUTS:
//    i = polynomial number
//    p = polynomial degree
//    x = x value
int bern(int i, int p, double x)
{
  if (p == 0 && i == 1)
    return 1;
  else if (i < 1 || i > p+1)
    return 0;
  else
    return (1-x)*bern(i,p-1,x) + x * bern(i-1,p-1,x);
}
