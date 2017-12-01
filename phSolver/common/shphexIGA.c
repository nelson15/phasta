//shphexIGA.c
//Build the data structures defining the structured grid IGA hex elements
#include <FCMangle.h>

int HexIGAShapeAndDrv(int p, int quadPtIndex, double N[], double dN[][1],
                      double C[][][]);

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
