//shphexIGA.c
//Build the data structures defining the structured grid IGA hex elements
#include <FCMangle.h>

int HexIGAShapeAndDrv(int p, int quadPtIndex, double N[], double dN[][1],
                      double C[][][]);
int bern(int i, int p, double x);

#define shphexIGA FortranCInterface_GLOBAL_(shphexIGA, SHPHEXIGA)
void shphexIGA(int *p, int quadPtIndex, double N[], double dN[][1], double C[][][])
{

  HexIGAShapeAndDrv(*p,quadPtIndex,N,dN);
  vector<double> knot_vec;
  double h = pi/(double)num_elem_1D;
  knotVecCreate(num_elem_1D, *p, 0.0, pi, h, &knot_vec);
  nshg = knot_vec.size() - p - 1;
  Extraction_1D(nshg, p, knot_vec, C);

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
