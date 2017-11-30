//shphexIGA.c
//Build the data structures defining the structured grid IGA hex elements
#include <FCMangle.h>

int HexIGAShapeAndDrv(int p,double par[3],double N[],double dN[][3],
                      double C[][][]);

#define shphexIGA FortranCInterface_GLOBAL_(shphexIGA, SHPHEXIGA)
void shphexIGA(int *p, double par[], double N[], double dN[][3], double C[][][])
{

  HexIGAShapeAndDrv(*p,par,N,dN,C);

}
